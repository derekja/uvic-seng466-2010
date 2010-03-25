#include "sonar.h"
#include "common.h"
#include "WProgram.h"
#include <util/delay.h>

static uint16_t timerTickCount = 0;
static double distance = 0;
/*
 * Array to store the rising edge and falling edge
 * timing. It has to be uint16_t because the timer
 * is a 16 bit timer with a prescaler of 64 so the
 * maximum value exceeds the range of value that
 * can be stored in a 8 bit number.
 */
static uint16_t risingEdgeTime[3];
static uint16_t fallingEdgeTime[3];

/*
 * SonarID determines which sonar has fired and let
 * the system assign the value to the correct sonar.
 * Sonar ID 0 = Front Sonar
 * Sonar ID 1 = Left Sonar
 * Sonar ID 2 = Right Sonar
 */
static uint8_t sonarID = 0;

void sonarInit() {
	// initialize the pins as inputs:
	pinMode(FRONT_SONAR_RX, OUTPUT);
	pinMode(FRONT_SONAR_PW, INPUT);

	Serial.println("Sonar Init");

	/*
	 * Assuming sonarInit() gets called immediately after
	 * power up, then a period of 250 ms must be passed
	 * before the RX pin is ready to receive command.
	 */
	_delay_ms(250);

	//Disable sonar echo firing when it is first initialized
	digitalWrite(FRONT_SONAR_RX, LOW);

	return;
}

double sonarMeasureDistance() {
	/*
	 * CS32 CS31 CS30 = 011
	 * Set clock prescaler factor to 64
	 * ICNC3 = noise canceler => enabled
	 * ICES3 = trigger edge => 0 = falling edge
	 */
	TCCR3B &= ~_BV(CS32);
	TCCR3B |= (_BV(CS30) | _BV(CS31));
	TCCR3B |= _BV(ICNC3);

	//Set timer 3 to Normal Mode
	TCCR3A &= ~(_BV(WGM30) | _BV(WGM31));
	TCCR3B &= ~(_BV(WGM32) | _BV(WGM33));

	Serial.println("Before ECHO");

	sonarEcho();

	_delay_ms(50);

	timerTickCount = fallingEdgeTime[0] - risingEdgeTime[0];

	Serial.println("After ECHO");

	Serial.print("Timer Tick Count: ");
	Serial.print(timerTickCount);
	Serial.println("");

	/*
	 * Clock is 16MHz, with a prescaler of 64, that means
	 * each timer tick is 4us. For the sonar, 147 us = 1 inch
	 * so we need to divide by 147 / 4 = 36.75.
	 */
	distance = timerTickCount / 36.75;

	Serial.print("Distance: ");
	Serial.print(distance);
	Serial.println("");

	return distance;
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
	digitalWrite(FRONT_SONAR_RX, HIGH);

	return;
}

ISR(TIMER3_CAPT_vect)
{
	/*
	 * Once the rising edge of PW is detected, it means
	 * RX has been staying HIGH long enough. Set it to
	 * LOW now to disable sonar.
	 */
	digitalWrite(FRONT_SONAR_RX, LOW);

	/*
	 * Reset Timer 3 when the rising edge of PW is
	 * detected, then change the Input Capture configuration
	 * to detect the falling edge and clear the interrupt flag.
	 */
	if (IS_RISING_EDGE()) {
		risingEdgeTime[sonarID] = ICR3;
		SET_FALLING_EDGE();
		CLEAR_IC_FLAG();
	} else {
		/*
		 * Store the ICR3 value and disable Input Capture
		 * so it does not interfere with other components.
		 */
		fallingEdgeTime[sonarID] = ICR3;
		SET_RISING_EDGE();
		CLEAR_IC_FLAG();
		SET_IC_DISABLE();
	}
}
