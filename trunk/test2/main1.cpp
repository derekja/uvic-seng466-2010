/*
 * main1.cpp
 *
 *  Created on: Jan 8, 2010
 *      Author: derekja
 */

#include <avr/io.h>
#include <avr/interrupt.h>
//#include "WProgram.h"
#include "Servotmp.h"

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// the next two lines are needed to hack around a serial monitor bug
extern "C" void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void) {}


 // The setup() method runs once, when the sketch starts

 void setup()   {
	 // set up serial
	 //Serial.begin( 57600 );
	 //Serial.print("start");

   //PWM ports go output by default, so don't need to set that
   //pinMode(servoPin, OUTPUT);
   //Serial.print("start");
   servoInit();
 }

 // the loop() method runs over and over again,
 // as long as the Arduino has power

 void loop()
 {

	 servoSet(0);

	 //delay(500);                  // wait for a second

 }

 int main() {
 //init();
		//sbi(TCCR4A, WGM40);
	    //TCCR4A = 0b000001;    // COM4B1, COM4B0, COM4C1, COM4C0, WGM41, and WGM40

 setup();
 //lastPulse = millis();
 for(;;) {
loop();
 }
 }
