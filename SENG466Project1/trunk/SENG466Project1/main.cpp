/*
 SENG466 Project 1
 */
#include "WProgram.h"
#include "wiring.h"
#include "Wire.h"
#include "common.h"
#include "sonar.h"
#include "led.h"

extern "C" void __cxa_pure_virtual() {
}

static bool color = 0;

void setup() {

	// Enable global interrupt
	Enable_Interrupt();

	// Initialize sonar
	sonarInit();

	// Initialize serial port
	Serial.begin(57600);

	// Initialize I2C/TwoWire
	Wire.begin();

	LEDSetAddress(1);
}

void loop() {
//	sonarMeasureDistance();

	if (color)
	{
		LEDSetColor(1, 255, 255, 0, true, true);
		color = !color;
	}
	else
	{
		LEDSetColor(1, 100, 100, 100, false, true);
		color = !color;
	}

	delay(2000);

	return;
}

int main() {
	init();
	setup();

	for (;;) {
		loop();
	}
}
