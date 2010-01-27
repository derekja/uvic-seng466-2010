#include <avr/io.h>
#include <avr/interrupt.h>
#include "sonar.h"
#include "common.h"
#include "WProgram.h"

static uint16_t timerTickCount = 0;
static double distance = 0;

void sonarInit() {
	// initialize the pins as inputs:
	pinMode(SonarRX, OUTPUT);
	pinMode(SonarPW, INPUT);

	/*
	 * Assuming sonarInit() gets called immediately after
	 * power up, then a period of 250 ms must be passed
	 * before the RX pin is ready to receive command.
	 */
	delay(250);

	//Disable sonar echo firing when it is first initialized
	digitalWrite(SonarRX, LOW);

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

	sonarEcho();

	delay(40);

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
	digitalWrite(SonarRX, HIGH);

	return;
}

ISR(TIMER3_CAPT_vect)
{
	// Disable global interrupt
	Disable_Interrupt();
	/*
	 * Once the rising edge of PW is detected, it means
	 * RX has been staying HIGH long enough. Set it to
	 * LOW now to disable sonar.
	 */
	digitalWrite(SonarRX, LOW);

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

	// Enable global interrupt
	Enable_Interrupt();
}
