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
	ACTUATE_TASK,
	CONTROL_TASK,
	SONAR_TASK,
};

const unsigned char PPP[10] = { ONBOARD_LED_HIGH, 1, ONBOARD_LED_LOW, 1, ACTUATE_TASK, 2, CONTROL_TASK, 2, SONAR_TASK, 90};
//const unsigned char PPP[8] = { ONBOARD_LED_HIGH, 1, ONBOARD_LED_LOW, 1, CONTROL_TASK, 200};
const unsigned int PT = sizeof(PPP) / 2;

extern void actuate();
extern void control();


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

void actuateTask(void) {
	while (true) {
		actuate();

		Task_Next();
	}
}

void controlTask(void) {
	while (true) {
		control();

		Task_Next();
	}
}

int r_main(void) {

	pinMode(ONBOARD_LED, OUTPUT);
	Serial.begin(57600);

//	pinMode(5, OUTPUT);
//	pinMode(6, OUTPUT);
//	pinMode(7, OUTPUT);
//
//	digitalWrite(5, LOW);
//	digitalWrite(6, HIGH);
//	analogWrite( 7, 255 );
//
//	while(true) {
//	analogWrite( 7, 255 );
//	_delay_ms(500);
//	Serial.println("hello");
//	analogWrite( 7, 0 );
//	_delay_ms(500);
//	Serial.println("world");
//	}

	sonarInit();
//	radioInitSetup();

	Task_Create(task1, ONBOARD_LED_HIGH, PERIODIC, ONBOARD_LED_HIGH);
	Task_Create(task2, ONBOARD_LED_LOW, PERIODIC, ONBOARD_LED_LOW);
	Task_Create(sonarTask, SONAR_TASK, PERIODIC, SONAR_TASK);
	Task_Create(actuateTask, ACTUATE_TASK, PERIODIC, ACTUATE_TASK);
	Task_Create(controlTask, CONTROL_TASK, PERIODIC, CONTROL_TASK);

	return 0;
}
