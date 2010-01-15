 /*
   Blink

  Turns on an LED on for one second, then off for one second, repeatedly.

  The circuit:
  * LED connected from digital pin 13 to ground.

  * Note: On most Arduino boards, there is already an LED on the board
  connected to pin 13, so you don't need any extra components for this example.


  Created 1 June 2005
  By David Cuartielles

  http://arduino.cc/en/Tutorial/Blink

  based on an orginal by H. Barragan for the Wiring i/o board

  */
#include "WProgram.h"

 int ledPin =  13;    // LED connected to digital pin 13

 // The setup() method runs once, when the sketch starts

 void setup()   {
   // initialize the digital pin as an output:
   pinMode(ledPin, OUTPUT);
   Serial.begin(57600);
   Serial1.begin(57600);
   Serial2.begin(57600);
   Serial3.begin(57600);
 }

 // the loop() method runs over and over again,
 // as long as the Arduino has power

 void loop()
 {
   digitalWrite(ledPin, HIGH);   // set the LED on
   delay(1000);                  // wait for a second
   digitalWrite(ledPin, LOW);    // set the LED off
   delay(1000);					 // wait for a second
   Serial.println("Hello World");
   Serial1.println("Hello World 1");
   Serial2.println("Hello World 2");
   Serial3.println("Hello World 3");
 }

 int main(){
	 init();
	 setup();

	 for(;;)
	 {
		loop();
	 }
 }
