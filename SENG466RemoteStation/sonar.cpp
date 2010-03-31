#include "sonar.h"
#include "common.h"
#include "WProgram.h"
#include <avr/delay.h>

static uint16_t timerTickCount = 0;

/*
 * SonarID determines which sonar has fired and let
 * the system assign the value to the correct sonar.
 * Sonar ID 0 = Front Sonar
 * Sonar ID 1 = Left Sonar
 * Sonar ID 2 = Right Sonar
 */
static uint8_t sonarID = 0;

/*
 * Map each of the sonarID to the actual port number
 */
static uint8_t PortMap[3] = {FRONT_SONAR_RX, LEFT_SONAR_RX, RIGHT_SONAR_RX};

/*
 * Index to the sonar buffer array that is used to store the data
 */
static uint8_t sonarBufferIndex = 0;

/*
 * xxxSonarBufer[20] holds 20 sonar readings for the
 * control module to use. sonarBufferPointer points
 * to the buffer location that should be used to store
 * the next sonar reading data
 */
uint16_t frontSonarBuffer[20];
uint16_t leftSonarBuffer[20];
uint16_t rightSonarBuffer[20];

void sonarInit() {
	/*
	 * CS32 CS31 CS30 = 011
	 * Set clock prescaler factor to 64
	 * ICNC3 = noise canceler => enabled
	 */
	TCCR3B &= ~_BV(CS32);
	TCCR3B |= (_BV(CS30) | _BV(CS31));
	TCCR3B |= _BV(ICNC3);

	//Set timer 3 to Normal Mode
	TCCR3A &= ~(_BV(WGM30) | _BV(WGM31));
	TCCR3B &= ~(_BV(WGM32) | _BV(WGM33));

	sonarBufferIndex = 0;

	/*
	 * Initialize the PW pin as input and all the
	 * RX pins of the sonar sensors as output
	 */
	pinMode(FRONT_SONAR_RX, OUTPUT);
	pinMode(LEFT_SONAR_RX, OUTPUT);
	pinMode(RIGHT_SONAR_RX, OUTPUT);

	/*
	 * Set PE7 to input
	 *
	 * DDRE |= _BV(PE7) means setting it to output
	 */
//	DDRE &= ~_BV(SONAR_PW);


	/*
	 * Assuming sonarInit() gets called immediately after
	 * power up, then a period of 250 ms must be passed
	 * before the RX pin is ready to receive command.
	 */
	_delay_ms(250);

	//Disable each sonar when they are first initialized
	digitalWrite(PortMap[0], LOW);
	digitalWrite(PortMap[1], LOW);
	digitalWrite(PortMap[2], LOW);

	return;
}

void sonarMeasureDistance() {
		sonarID = 0;

	/*
	 * Clock is 16MHz, with a prescaler of 64, that means
	 * each timer tick is 4us. For the sonar, 147 us = 1 inch
	 * so we need to divide by 147 / 4 = 36.75.
	 */

	/*
	 * Front sonar reading
	 */
	sonarEcho();
	_delay_ms(50);
	frontSonarBuffer[sonarBufferIndex] = timerTickCount / 36.75;
	Serial.print("Front Sonar: ");
	Serial.print((int)frontSonarBuffer[sonarBufferIndex]);
	Serial.println();

	/*
	 * Left sonar reading
	 */
	++sonarID;
	sonarEcho();
	_delay_ms(50);
	leftSonarBuffer[sonarBufferIndex] = timerTickCount / 36.75;
	Serial.print("Left Sonar: ");
	Serial.print((int)leftSonarBuffer[sonarBufferIndex]);
	Serial.println();

	/*
	 * Right sonar reading
	 */
	++sonarID;
	sonarEcho();
	_delay_ms(50);
	rightSonarBuffer[sonarBufferIndex] = timerTickCount / 36.75;
	Serial.print("Right Sonar: ");
	Serial.print((int)rightSonarBuffer[sonarBufferIndex]);
	Serial.println();

	/*
	 * sonarBufferIndex should always be between
	 * 0 and 19 since only 20 data readings should
	 * be kept.
	 */
	++sonarBufferIndex;

	if (sonarBufferIndex >= 20)
	{
		sonarBufferIndex = 0;
	}

//	int i;
//
//	Serial.print("Front Sonar Reading:\t");
//	for (i = 0; i < 20; ++i)
//	{
//		Serial.print((int)frontSonarBuffer[i]);
//		Serial.print(" ");
//	}
//	Serial.println();
//
//	Serial.print("Left Sonar Reading:\t");
//	for (i = 0; i < 20; ++i)
//	{
//		Serial.print((int)leftSonarBuffer[i]);
//		Serial.print(" ");
//	}
//	Serial.println();
//
//	Serial.print("Right Sonar Reading:\t");
//	for (i = 0; i < 20; ++i)
//	{
//		Serial.print((int)rightSonarBuffer[i]);
//		Serial.print(" ");
//	}
//	Serial.println();

	return;
}

/**
 * Set Input Capture to look for a rising edge, clear
 * the interrupt flag and then enable Input Capture.
 * After that, set RX to HIGH to enable the sonar.
 */
void sonarEcho() {
	SET_RISING_EDGE();
	CLEAR_IC_FLAG();
	SET_IC_ENABLE();

	//Enable Sonar
	digitalWrite(PortMap[sonarID], HIGH);

	return;
}

ISR(TIMER3_CAPT_vect)
{
	/*
	 * Once the rising edge of PW is detected, it means
	 * RX has been staying HIGH long enough. Set it to
	 * LOW now to disable sonar.
	 */
	digitalWrite(PortMap[sonarID], LOW);

	/*
	 * Reset Timer 3 when the rising edge of PW is
	 * detected, then change the Input Capture configuration
	 * to detect the falling edge and clear the interrupt flag.
	 */
	if (IS_RISING_EDGE()) {
		TCNT3 = 0;
		SET_FALLING_EDGE();
		CLEAR_IC_FLAG();
	} else {
		/*
		 * Store the ICR3 value and disable Input Capture
		 * so it does not interfere with other components.
		 */
		timerTickCount = ICR3;
		SET_RISING_EDGE();
		CLEAR_IC_FLAG();
		SET_IC_DISABLE();
	}
}
