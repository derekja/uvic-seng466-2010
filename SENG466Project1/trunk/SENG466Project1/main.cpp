/*
 SENG466 Project 1
 */
#include "Arduino/WProgram.h"
#include "Arduino/wiring.h"
#include "Wire.h"
#include "common.h"
#include "sonar.h"

extern "C" void __cxa_pure_virtual() {
}

void setup() {

	Enable_Interrupt();

	sonarInit();

	Serial.begin(57600);

	Wire.begin();

	Wire.beginTransmission(0x00); // general call (broadcast address)
	Wire.send('A');
	Wire.send(2);
	Wire.send(0xD0);
	Wire.send(0x0D); // dood!
	Wire.send(2);
	Wire.endTransmission();
	delay(50); // just in case

	Wire.beginTransmission(2);
	Wire.send('n');
	Wire.send(255);
	Wire.send(0);
	Wire.send(0);
	Wire.send('o');
	Wire.endTransmission();

	delay(5000);

	Wire.beginTransmission(2);
	Wire.send('n');
	Wire.send(0);
	Wire.send(255);
	Wire.send(0);
	Wire.send('o');
	Wire.endTransmission();

}

void loop() {
	/*
	 digitalWrite(ledPin, HIGH);   // set the LED on
	 delay(500);                  // wait for a second
	 digitalWrite(ledPin, LOW);    // set the LED off
	 delay(500);					 // wait for a second
	 Serial.println("Hello World");
	 */
	sonarMeasureDistance();
	delay(500);
}

int main() {
	init();
	setup();

	for (;;) {
		loop();
	}
}
