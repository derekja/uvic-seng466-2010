/*
 * servo.cpp
 *
 *  Created on: Jan 22, 2010
 *      Author: derekja
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "servo.h"
#include "common.h"
#include "WProgram.h"

static int servoValue = 0;
static int hitanint = 0;

void servoInit() {
	// initialize the servo pin as an output:
	// equiv to DDRL |= _BV(PL5);
	pinMode(ServoPin, OUTPUT);

    //Set top to 20000 (which will be 20ms with the prescaler set later)
    OCR5A = 20000;

    //the time it should be up for no movement is 2397, this is just an initial value
    //it gets set to servoValue the first time the interrupt is hit
    OCR5C = 2397;
	// put the servo to it's neutral position, will vary by servo
	servoValue = 2397;

	// start 0C5C high, down on match (COM5C1 and COM5C0) WGM are for waveform generation
	// top is in OCR5A, fast PWM
	TCCR5A |= (_BV(COM5C1) | _BV(WGM50) | _BV(WGM51));
	TCCR5B |= (_BV(WGM52) | _BV(WGM53));
	TCCR5A &= ~_BV(COM5C0);

	//Set the prescaler to 8
	TCCR5B |= _BV(CS51);
	TCCR5B &= ~(_BV(CS52) | _BV(CS50));

	Serial.print("servoInit");

	return;
}

void servoSet(int value) {

	servoValue = value;
	Serial.print(hitanint);
	Serial.println();

	return;
}

ISR(TIMER5_CAPT_vect)
{
	// Disable global interrupt
	Disable_Interrupt();

	//when we hit the overflow all we need to do is turn on the pin
	// this should hit every 20msecs as per the TOP value in the init
	digitalWrite(ServoPin, HIGH);

	hitanint = 1;

	//reset the servoValue in case it has been updated this last cycle
	OCR5C = servoValue;

	// Enable global interrupt
	Enable_Interrupt();
}

ISR(TIMER5_COMPC_vect)
{
	// Disable global interrupt
	Disable_Interrupt();

	Serial.print("compC");

	//when we hit the C comparator all we need to do is turn the pin back off
	// this should hit every servoValue microseconds as per the TOP value in the init
	digitalWrite(ServoPin, LOW);

	// Enable global interrupt
	Enable_Interrupt();
}
