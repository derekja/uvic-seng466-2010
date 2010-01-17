/*
 SENG466 Project 1
  */
#include "WProgram.h"
#include "common.h"
#include "sonar.h"

extern "C" void __cxa_pure_virtual() {
}

void setup() {

	sonar_init();

	Serial.begin(57600);
}

void loop() {
	/*
	 digitalWrite(ledPin, HIGH);   // set the LED on
	 delay(500);                  // wait for a second
	 digitalWrite(ledPin, LOW);    // set the LED off
	 delay(500);					 // wait for a second
	 Serial.println("Hello World");
	 */
}

int main() {
	init();
	setup();

	for (;;) {
		loop();
	}
}
