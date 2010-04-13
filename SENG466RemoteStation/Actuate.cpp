/*
 * Actuate.cpp
 *
 *  Created on: Mar 25, 2010
 *      Author: jensweber
 */

#include "Actuate.h"
#include "WProgram.h"

int old_left_propulsion;
int old_right_propulsion;

int left_propulsion;
int right_propulsion;

int left_propulsion_scaled;
int right_propulsion_scaled;

extern int speed_right;
extern int speed_left;

void actuate()
{

	right_propulsion = speed_right + 25;
	right_propulsion = ( 2 * old_right_propulsion + right_propulsion ) / 3;//damp value
	old_right_propulsion = right_propulsion;
	right_propulsion_scaled = ( right_propulsion * 255 ) / 100;//scale value

	left_propulsion = speed_left + 25;
	left_propulsion = ( 2 * old_left_propulsion + left_propulsion ) / 3;//damp value
	old_left_propulsion = left_propulsion;
	left_propulsion_scaled = ( left_propulsion * 255 ) / 100;//scale value

	if( left_propulsion_scaled == 0 && right_propulsion_scaled == 0)
	{
		digitalWrite( LEFT_MOTOR_PIN_E, 0 );
		digitalWrite( RIGHT_MOTOR_PIN_E, 0 );
		return;
	}
	else
	{
		if( left_propulsion_scaled > 0 )
		{
			digitalWrite( LEFT_MOTOR_PIN_1, 0 );
			digitalWrite( LEFT_MOTOR_PIN_2, 1 );
		}
		else
		{
			digitalWrite( LEFT_MOTOR_PIN_1, 1 );
			digitalWrite( LEFT_MOTOR_PIN_2, 0 );
		}

		analogWrite( LEFT_MOTOR_PIN_E, left_propulsion_scaled );

		if( right_propulsion_scaled > 0 )
		{
			digitalWrite( RIGHT_MOTOR_PIN_1, 1 );
			digitalWrite( RIGHT_MOTOR_PIN_2, 0 );
		}
		else
		{
			digitalWrite( RIGHT_MOTOR_PIN_1, 0 );
			digitalWrite( RIGHT_MOTOR_PIN_2, 1 );
		}

		analogWrite( RIGHT_MOTOR_PIN_E, right_propulsion_scaled );
	}
}
