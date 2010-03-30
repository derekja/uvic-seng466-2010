#include <stdio.h>
#include "os.h"
#include "WProgram.h"
#include "common.h"
#include "sonar.h"
#include <avr/delay.h>

enum {
	ONBOARD_LED_HIGH = 1,
	ONBOARD_LED_LOW,
};

const unsigned char PPP[4] = {ONBOARD_LED_HIGH, 100, ONBOARD_LED_LOW, 100};
const unsigned int PT = sizeof(PPP)/2;

void task1(void)
{
    for(;;)
    {
   		digitalWrite(ONBOARD_LED, HIGH);
    	sonarMeasureDistance();

        Task_Next();
    }
}

void task2(void)
{
    for(;;)
    {
   		digitalWrite(ONBOARD_LED, LOW);
//    	sonarMeasureDistance();

        Task_Next();
    }
}


int r_main(void)
{
	init();

	pinMode(13, OUTPUT);
	Serial.begin(57600);
	sonarInit();

	Task_Create(task1, ONBOARD_LED_HIGH, PERIODIC, ONBOARD_LED_HIGH);
	Task_Create(task2, ONBOARD_LED_LOW, PERIODIC, ONBOARD_LED_LOW);

   	return 0;
}
