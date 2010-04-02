#include <avr/delay.h>
#include <stdio.h>
#include "os.h"
#include "WProgram.h"
#include "common.h"
#include "sonar.h"
#include "radioclient.h"

/*
 * 0 is reserved for IDLE task, so the enumeration
 * must start at 1.
 */
enum {
	ONBOARD_LED_HIGH = 1,
	ONBOARD_LED_LOW,
	SONAR_TASK,
};

const unsigned char PPP[6] = { ONBOARD_LED_HIGH, 50, ONBOARD_LED_LOW, 50, SONAR_TASK, 200};
const unsigned int PT = sizeof(PPP) / 2;

void task1(void) {
	for (;;) {
		digitalWrite(ONBOARD_LED, HIGH);

		Task_Next();
	}
}

void task2(void) {
	for (;;) {
		digitalWrite(ONBOARD_LED, LOW);

		Task_Next();
	}
}

void sonarTask(void) {
	while (true) {
		sonarMeasureDistance();

		Task_Next();
	}
}

int r_main(void) {

	pinMode(ONBOARD_LED, OUTPUT);
	Serial.begin(57600);

//	pinMode(37, OUTPUT);
//	pinMode(36, OUTPUT);
//	pinMode(35, OUTPUT);
//
//	while(true){
//		digitalWrite(37, HIGH);
//		digitalWrite(36, HIGH);
//		digitalWrite(35, HIGH);
//		_delay_ms(1000);
//		digitalWrite(37, LOW);
//		digitalWrite(36, LOW);
//		digitalWrite(35, LOW);
//		_delay_ms(1000);
//
//	}

	sonarInit();
	radioInitSetup();

	Task_Create(task1, ONBOARD_LED_HIGH, PERIODIC, ONBOARD_LED_HIGH);
	Task_Create(task2, ONBOARD_LED_LOW, PERIODIC, ONBOARD_LED_LOW);
	Task_Create(sonarTask, SONAR_TASK, PERIODIC, SONAR_TASK);

	return 0;
}
