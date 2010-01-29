/*
 SENG466 Project 1
 */
#include "WProgram.h"
#include "wiring.h"
#include "Wire.h"
#include "common.h"
#include "led.h"
#include "radioclient.h"
#include "string.h"
#include <ctype.h>

/*
 * This function should never be called under normal operation
 */
extern "C" void __cxa_pure_virtual() {
	Disable_Interrupt();
	while (1)
		;
}

int XPosition;
int YPosition;
int SonarDistance;

char xstring[5];
char ystring[5];
char message[20];
char *slash = "/";

void setup() {

	// Enable global interrupt
	Enable_Interrupt();

	// Initialize serial port
	Serial.begin(57600);

	// Initialize I2C/TwoWire
	Wire.begin();

	LEDSetAddress(1);
	radioInitSetup();
}

void loop() {
	XPosition = analogRead(X_AXIS);
	YPosition = analogRead(Y_AXIS);

	/*
	 * Turn on the on-board LED if the button
	 * on the joystick is pressed; otherwise,
	 * turn it off
	 */
	if (analogRead(JOYSTICK_BUTTON)) {
		digitalWrite(ONBOARD_LED, LOW);
	} else {
		digitalWrite(ONBOARD_LED, HIGH);
	}

	message[0] = '\0';
	itoa(XPosition, xstring, 10);
	itoa(YPosition, ystring, 10);

	strcat(message, xstring);
	strcat(message, slash);
	strcat(message, ystring);

	sendMsg(message);

	LEDSetColor(1, 0, DistanceToIntensity(SonarDistance), 0, false, true);
	delay(200);
	return;
}

uint8_t DistanceToIntensity(int distance) {
	SonarDistance = distance;
	if (distance > 255) {
		SonarDistance = 255;
	} else if (distance < 0) {
		SonarDistance = 0;
	}

	return SonarDistance;
}

void GetSonarDistance(char *SonarDistanceBuffer) {
	SonarDistance = -1;

	if (strncmp(SonarDistanceBuffer, "dist: ", 6) == 0) {
		while (*SonarDistanceBuffer && !isdigit(*SonarDistanceBuffer)) {
			SonarDistanceBuffer++;
		}
		SonarDistance = atoi(SonarDistanceBuffer);
		Serial.println(SonarDistance);
	}
}

int main() {
	init();
	setup();

	// Set external LED initial color to green
	LEDSetColor(1, 0, 255, 0, false, true);

	// Turn off the onboard LED
	digitalWrite(ONBOARD_LED, LOW);

	for (;;) {
		loop();
	}
}
