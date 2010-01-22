/*
 * main1.cpp
 *
 *  Created on: Jan 8, 2010
 *      Author: derekja
 */

#include "WProgram.h"
//#include "Servo.h"
// the next two lines are needed to hack around a serial monitor bug
extern "C" void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void) {}

int ledPin =  13;    // LED connected to digital pin 13
int motor1Pin1 = 2;
int motor1Pin2 = 3;
int pot = 0;
//Servo servoMotor;
int servoPin = 10;
int servoValue = 0;
long lastPulse = 0;    // the time in milliseconds of the last pulse
int refreshTime = 20; // the time needed in between pulses


 // The setup() method runs once, when the sketch starts

 void setup()   {
	 // set up serial
	 Serial.begin( 57600 );
	 Serial.print("start");
   // initialize the digital pin as an output:
   pinMode(ledPin, OUTPUT);
   // init the pot as an input
   pinMode(pot, INPUT);
   //PWM ports go output by default, so don't need to set that
   pinMode(servoPin, OUTPUT);
   //attach the servo
   //servoMotor.attach(servoPin);
 }

 // the loop() method runs over and over again,
 // as long as the Arduino has power

 int getPot() {
	 int v;
	 v = analogRead(pot) / 4;
	 //Serial.print( v );
	 //Serial.println();
	 return v;
 }

 void loop()
 {
	 int d = 0; // initial var for which motor pin
	 int s = 0; // initial var for speed
	 int v = getPot();
	 //Serial.print(servoValue);
	 servoValue = map(v, 0, 255, 500, 5000);
	 Serial.print(servoValue);
	 Serial.println();
	 if (v<80) {
		 d = 1;
		 s = 255-(v*2);
	 }
	 if (v>110) {
		 d = 2;
		 s = v;
	 }
	 switch (d) {
	 case 1 :
		 analogWrite(motor1Pin1, s);
		 analogWrite(motor1Pin2, 0);
		 break;

	 case 2 :
		 analogWrite(motor1Pin1, 0);
		 analogWrite(motor1Pin2, s);
		 break;

	 default :
		 analogWrite(motor1Pin1, 0);
		 analogWrite(motor1Pin2, 0);
		 servoValue = 2397;
	 }
	 //servoMotor.write(servoValue);

	  // pulse the servo again if rhe refresh time (20 ms) have passed:
	  if (millis() - lastPulse >= refreshTime) {
	    digitalWrite(servoPin, HIGH);   // Turn the motor on
	    delayMicroseconds(servoValue);       // Length of the pulse sets the motor position
	    digitalWrite(servoPin, LOW);    // Turn the motor off
	    lastPulse = millis();           // save the time of the last pulse
	  }

   //analogWrite(motor1Pin1, 255);
	// analogWrite(motor1Pin1, 0);
	// analogWrite(motor1Pin2, 255);
	// delay(1000);                  // wait for a second
	// analogWrite(motor1Pin1, 128);
	// analogWrite(motor1Pin2, 0);
   //digitalWrite(ledPin, LOW);    // set the LED off
	 //delay(1000);                  // wait for a second
	 // test2
 }

 int main() {
 init();
 setup();
 digitalWrite(ledPin, HIGH);   // set the LED on
 //lastPulse = millis();
 for(;;) {
loop();
 }
 }
