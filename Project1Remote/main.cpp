/*
 SENG466 Project 1
 */
#include "WProgram.h"
#include <stdio.h>
#include "wiring.h"
#include "Wire.h"
#include "common.h"
#include "sonar.h"
#include "servo.h"
#include "radioclient.h"

// the next two lines are needed to hack around a serial monitor bug
extern "C" void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void) {}

int pot = 0; //this is temporary for testing until the radio goes in
unsigned int servoVal = 0; //global to hold servo value in microseconds
uint8_t sreg = 0;
int motor1Pin1 = 11;
int motor1Pin2 = 12;
int d = 0; // initial var for which motor pin
int s = 0; // initial var for speed
int v = 0; //hold value of pot
double dist = 0; //hold distance measurements
char dist_char [20]; //to pass dist to radio

void setup() {

	// init the pot as an input (temp)
	pinMode(pot, INPUT);

	//init the pwms
	pinMode(motor1Pin1, OUTPUT);
	pinMode(motor1Pin2, OUTPUT);
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

	// init and setup radio
	radioInitSetup();
}

void loop() {
	dist = sonarMeasureDistance();
	/*v = analogRead(pot);
	d = 0; // initial var for which motor pin
	s = 0; // initial var for speed
	servoVal = map(v,0,1024,1800, 4200);
	v = v/4;
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
		 servoVal = 3000;
	 }
	servoSet(servoVal);
*/
	sprintf(dist_char, "dist: %d", (int)dist);
	sendMsg(dist_char);

	Serial.print(dist_char);
	Serial.println();

	//Serial.print(v*4);



	delay(500);


	return;
}

int main() {
	init();
	setup();

	for (;;) {
		loop();
	}
}
