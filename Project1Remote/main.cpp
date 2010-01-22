/*
 SENG466 Project 1
 */
#include "WProgram.h"
#include "wiring.h"
#include "Wire.h"
#include "common.h"
#include "sonar.h"

// the next two lines are needed to hack around a serial monitor bug
extern "C" void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void) {}

void setup() {

	// Enable global interrupt
	Enable_Interrupt();

	// Initialize sonar
	sonarInit();

	// Initialize serial port
	Serial.begin(57600);

	// Initialize I2C/TwoWire
	Wire.begin();


}

void loop() {
	sonarMeasureDistance();

	delay(500);

	Serial.print("hello world");

	return;
}

int main() {
	init();
	setup();

	for (;;) {
		loop();
	}
}
