/*
 * This file defines the common variables needed by the project.
 */
#ifndef COMMON_H_
#define COMMON_H_

#define TRUE 1
#define FALSE 0
#define ONBOARD_LED 13

#define Disable_Interrupt()  asm volatile ("cli"::)
#define Enable_Interrupt()   asm volatile ("sei"::)

typedef enum {
	LEFT_SONAR,
	RIGHT_SONAR,
	FRONT_SONAR
} sonarID;

const int STOP = 0;
const int FOLLOW_WALL = 1;
const int TURN = 2;
const int AVOID_OBSTACLE = 3;

#endif /* COMMON_H_ */
