//#include <avr/io.h> //needed for register names, disabled for now
#include "sonar.h"
#include "common.h"
#include "Arduino/WProgram.h"

void sonar_init() {
	// initialize the pins as inputs:
	pinMode(SonarRX, OUTPUT);
	pinMode(SonarPW, INPUT);

	/*
	 * Assuming sonar_init() gets called immediately after power up, then a
	 * period of 250 ms must be passed before the RX pin is ready to receive
	 * command.
	 */
	delay(250);

	//Disable sonar echo firing when it is first initialized
	digitalWrite(SonarRX, LOW);

}
