/*
 * Control.cpp
 *
 *  Created on: Mar 25, 2010
 *      Author: jensweber
 */

#include "Control.h"
#include "Arduino/WProgram.h"
#include "common.h"

/*prototypes*/
extern uint16_t sonarGetDistance( int sonar );

int speed_right;
int speed_left;


extern int command;

int state = FOLLOW_WALL;

const int FOLLOW_WALL_SET_POINT_RIGHT = 30;
const int FOLLOW_WALL_SPEED_RIGHT = 100;

int follow_wall_prev_error_right;
int follow_wall_error_right;
int follow_wall_old_error_right;
int follow_wall_p_right;
int FOLLOW_WALL_KP_RIGHT = 8;
int follow_wall_d_right;
int FOLLOW_WALL_KD_RIGHT = 4;
int follow_wall_i_right;
int FOLLOW_WALL_KI_RIGHT = 2;

const int FOLLOW_WALL_SET_POINT_LEFT = 24;
const int FOLLOW_WALL_SPEED_LEFT = 100;

int follow_wall_prev_error_left;
int follow_wall_error_left;
int follow_wall_old_error_left;
int follow_wall_p_left;
int FOLLOW_WALL_KP_LEFT = 8;
int follow_wall_d_left;
int FOLLOW_WALL_KD_LEFT = 4;
int follow_wall_i_left;
int FOLLOW_WALL_KI_LEFT = 2;

void control()
{
	int temp1;
	int temp2;

	switch( state )
		{
			case STOP:
				state = command;
				break;
			case FOLLOW_WALL:
				temp1 = sonarGetDistance( LEFTFRONT_SONAR );
				temp2 = sonarGetDistance( LEFTBACK_SONAR );
				follow_wall_error_right = temp2 - FOLLOW_WALL_SET_POINT_RIGHT;

				//				follow_wall_error_right = sonarGetDistance( LEFTBACK_SONAR ) - FOLLOW_WALL_SET_POINT_RIGHT;
				follow_wall_p_right = follow_wall_error_right;
				follow_wall_d_right = follow_wall_error_right - follow_wall_prev_error_right;
				follow_wall_i_right = ( 2 * follow_wall_old_error_right )/3 + follow_wall_error_right/3;
				follow_wall_prev_error_right = follow_wall_error_right;
				follow_wall_old_error_right = follow_wall_i_right;

				//this scaling factor of 1/3 should keep the value between 100 and -100;
				speed_right = ( FOLLOW_WALL_KP_RIGHT*follow_wall_p_right
						+ FOLLOW_WALL_KD_RIGHT*follow_wall_d_right
						+ FOLLOW_WALL_KI_RIGHT*follow_wall_i_right )/3 - 25;

				Serial.print( "Left Back Sonar" );
				Serial.println( follow_wall_error_right + FOLLOW_WALL_SET_POINT_RIGHT );
				Serial.print( "Speed: " );
				Serial.println( speed_right );
				Serial.print("Left Back Sonar Value: ");
				Serial.println(temp2);

				follow_wall_error_left = temp1 - FOLLOW_WALL_SET_POINT_LEFT;

//				follow_wall_error_left = sonarGetDistance( LEFTFRONT_SONAR ) - FOLLOW_WALL_SET_POINT_LEFT;
				follow_wall_p_left = follow_wall_error_left;
				follow_wall_d_left = follow_wall_error_left - follow_wall_prev_error_left;
				follow_wall_i_left = ( 2 * follow_wall_old_error_left )/3 + follow_wall_error_left/3;
				follow_wall_prev_error_left = follow_wall_error_left;
				follow_wall_old_error_left = follow_wall_i_left;

				//this scaling factor of 1/3 should keep the value between 100 and -100;
				speed_left = ( FOLLOW_WALL_KP_LEFT*follow_wall_p_left
						+ FOLLOW_WALL_KD_LEFT*follow_wall_d_left
						+ FOLLOW_WALL_KI_LEFT*follow_wall_i_left )/3 - 25;

				Serial.print( "Left Front Sonar" );
				Serial.println( follow_wall_error_left + FOLLOW_WALL_SET_POINT_LEFT );
				Serial.print( "Speed: " );
				Serial.println( speed_left );
				Serial.print("Left Front Sonar Value: ");
				Serial.println(temp1);

//				state = command;
				break;
//			case TURN:
//				speed = 0;
//				if( yaw says we've stopped)
//				{
//					turn = 50;
//					delay( 1000 );//wait for a bit while we reorient
//					while( !( sonar( FRONT ) > OBSTACLE_AVOIDANCE_THREASHOLD );
//					turn = 0;
//					speed = SPEED;
//					while( sonar( RIGHT ) > FOLLOW_WALL_SET_POINT_RIGHT );
//					state = FOLLOW_WALL;
//				}
//				break;
			default:
				break;
		}
  }

