/*
 * This file defines the common variables needed by the project.
 * Pin assignments should be declared here to avoid collision.
 */

#ifndef __COMMON_H__
#define __COMMON_H__

#define TRUE 1
#define FALSE 0

#define Disable_Interrupt()  asm volatile ("cli"::)
#define Enable_Interrupt()   asm volatile ("sei"::)

static int SonarRX = 4; // Sonar RX pin is connected to pin 4
static int SonarPW = 9; // Sonar PW pin is connected to pin 9, ICP3 is on PE7


#endif
