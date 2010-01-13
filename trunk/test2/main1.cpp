/*
 * main1.cpp
 *
 *  Created on: Jan 8, 2010
 *      Author: derekja
 */

#include "WProgram.h"

//int ledPin =  13;    // LED connected to digital pin 13
int motor1Pin1 = 2;
int motor1Pin2 = 3;

 // The setup() method runs once, when the sketch starts

 void setup()   {
   // initialize the digital pin as an output:
   //pinMode(ledPin, OUTPUT);
   // init the two motor output pins
   //pinMode(motor1Pin1, OUTPUT);
   //pinMode(motor1Pin2, OUTPUT);
 }

 // the loop() method runs over and over again,
 // as long as the Arduino has power

 void loop()
 {
   //digitalWrite(ledPin, HIGH);   // set the LED on
   //analogWrite(motor1Pin1, 255);
	 analogWrite(motor1Pin1, 0);
	 analogWrite(motor1Pin2, 255);
	 delay(1000);                  // wait for a second
	 analogWrite(motor1Pin1, 128);
	 analogWrite(motor1Pin2, 0);
   //digitalWrite(ledPin, LOW);    // set the LED off
	 delay(1000);                  // wait for a second
 }

 int main() {
 init();
 setup();
 for(;;) {
 loop();
 }
 }
