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

extern "C" void __cxa_pure_virtual() {
}

static int button = 7;
static int xaxis = 6;
static int yaxis = 5;
int xpos;
int ypos;
int but;
char xstring[5];
char ystring[5];
char message[20];
char* slash = "/";

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
//	sonarMeasureDistance();
	xpos = analogRead(xaxis);
	Serial.println(xpos);
	Serial.print(" ");
	ypos = analogRead(yaxis);
	Serial.println(ypos);
	Serial.print(" ");
	but = analogRead(button);
	Serial.println(but);
	Serial.print(" ");
	Serial.println();

	message[0] = '\0';
	itoa(xpos, xstring, 10);
	itoa(ypos, ystring, 10);

	strcat(message, xstring);
	strcat(message, slash);
	strcat(message, ystring);



	sendMsg(message);
	delay(200);
Serial.print(message);
Serial.println();
	return;
}

int main() {
	init();
	setup();

	for (;;) {
		loop();
	}
}
