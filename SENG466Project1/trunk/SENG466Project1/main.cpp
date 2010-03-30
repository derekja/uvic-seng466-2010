/*
 SENG466 Project 1
 */
#include "WProgram.h"
#include "wiring.h"
//#include "Wire.h"
#include "common.h"
#include "radioclient.h"
#include "LiquidCrystal.h"
#include "vrbot_protocol.h"
#include "string.h"
#include <ctype.h>



/*
 * This function should never be called under normal operation
 */

LiquidCrystal lcd(10, 9, 8, 7, 6, 5);


int SonarDistance;




void setup() {

    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");

	//set up vrbot for speech reco
	vrbot_setup();
	  lcd.print("hello, world!2");
	// Enable global interrupt
	Enable_Interrupt();

	// Initialize serial port
	Serial.begin(9600);

	  lcd.print("hello, world!3");
	radioInitSetup();
}

void loop() {

	//Serial.print("test");

	SD_Recognition();

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

	// Set lcd enable pin to high
	//digitalWrite(9, HIGH);
	//digitalWrite(10, LOW);

	// Set external LED initial color to green
	//LEDSetColor(1, 0, 255, 0, false, true);

	// Turn off the onboard LED
	//digitalWrite(ONBOARD_LED, LOW);

	for (;;) {
		loop();
	}
}
