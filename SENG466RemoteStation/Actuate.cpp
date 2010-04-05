/*
 * Actuate.cpp
 *
 *  Created on: Mar 25, 2010
 *      Author: jensweber
 */

#include "Actuate.h"

void actuate()
{
	while( true )
	{
		switch ( d )
		{
			 case 1 :
				 analogWrite( motor1Pin1, fanVal );
				 analogWrite( motor1Pin2, 0 );
				 analogWrite( motor2Pin1, fanVal1 );
				 analogWrite( motor2Pin2, 0 );
				 break;

			 case 2 :
				 analogWrite( motor1Pin1, 0 );
				 analogWrite( motor1Pin2, fanVal );
				 analogWrite( motor2Pin1, 0 );
				 analogWrite( motor2Pin2, fanVal1 );
				 break;

			 default :
				 analogWrite( motor1Pin1, 0 );
				 analogWrite( motor1Pin2, 0 );
				 analogWrite( motor2Pin1, 0 );
				 analogWrite( motor2Pin2, 0 );
		 }

		//wait for next cycle
		task_next();
	}
}
