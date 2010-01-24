/*
 SENG466 Project 1
 */
#include "WProgram.h"
#include "wiring.h"
#include "Wire.h"
#include "common.h"
#include "sonar.h"
#include "servo.h"

// the next two lines are needed to hack around a serial monitor bug
extern "C" void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void) {}

int pot = 0; //this is temporary for testing until the radio goes in
int servoVal = 0; //global to hold servo value in microseconds

void setup() {

	// init the pot as an input (temp)
	pinMode(pot, INPUT);

	// Enable global interrupt
	Enable_Interrupt();

	// Initialize sonar
	sonarInit();

	// Initialize serial port
	Serial.begin(57600);

	// Initialize I2C/TwoWire
	Wire.begin();


	// init servo
	servoInit();

}

void loop() {
	sonarMeasureDistance();
	int v = analogRead(pot);
	servoVal = map(v,0,1024,544, 5000);
	servoSet(servoVal);

	Serial.print(servoVal);

	delay(500);

	//Serial.print("hello world");

	return;
}

int main() {
	init();
	setup();

	for (;;) {
		loop();
	}
}
