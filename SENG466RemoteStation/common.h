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

#define FRONT_SONAR_RX 4
#define FRONT_SONAR_PW 9

#endif /* COMMON_H_ */
