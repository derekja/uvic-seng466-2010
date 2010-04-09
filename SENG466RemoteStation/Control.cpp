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
int yaw();

int speed;
int turn;


extern int command;

int state = STOP;

const int FOLLOW_WALL_SET_POINT = 24;
const int FOLLOW_WALL_SPEED = 100;

int follow_wall_prev_error;
int follow_wall_error;
int follow_wall_old_error;
int follow_wall_p;
int FOLLOW_WALL_KP = 8;
int follow_wall_d;
int FOLLOW_WALL_KD = 4;
int follow_wall_i;
int FOLLOW_WALL_KI = 2;
int follow_wall_turn;

const int YAW_SETPOINT = 0;

int yaw_prev_error;
int yaw_error;
int yaw_old_error;
int yaw_p;
int yaw_kp = 8;
int yaw_d;
int yaw_kd = 4;
int yaw_i;
int yaw_ki = 2;
int yaw_turn;

void control()
{
	Serial.print( "control" );
//		switch( state )
//		{
//			case STOP:
//				state = command;
//				break;
//			case FOLLOW_WALL:
//
//				if( yaw() > 0 )
//				{
//					yaw_error = yaw() - YAW_SETPOINT;
//				}
//				else
//				{
//					yaw_error = - ( -yaw() - YAW_SETPOINT );
//				}
//				yaw_p = yaw_error;
//				yaw_d = yaw_error - yaw_prev_error;
//				yaw_i = ( 2 * yaw_old_error )/3 + yaw_error/3;
//				yaw_prev_error = yaw_error;
//				yaw_old_error = yaw_i;
//				yaw_turn = ( yaw_kp*yaw_p
//								+ yaw_kd*yaw_d
//								+ yaw_ki*yaw_i )/1600;//that scaling factor of 1/X should keep the value between 100 and -100

//
//				follow_wall_error = sonarGetDistance( RIGHT_SONAR ) - FOLLOW_WALL_SET_POINT;
//				follow_wall_p = follow_wall_error;
//				follow_wall_d = follow_wall_error - follow_wall_prev_error;
//				follow_wall_i = ( 2 * follow_wall_old_error )/3 + follow_wall_error/3;
//				follow_wall_prev_error = follow_wall_error;
//				follow_wall_old_error = follow_wall_i;
//				follow_wall_turn = ( FOLLOW_WALL_KP*follow_wall_p
//										+ FOLLOW_WALL_KD*follow_wall_d
//										+ FOLLOW_WALL_KI*follow_wall_i )/3;//that scaling factor of 1/3 should keep the value between 100 and -100
//
////				turn = ( 2*yaw_turn + follow_wall_turn )/3;
//				turn = follow_wall_turn;
//				speed = FOLLOW_WALL_SPEED;
//				state = command;
//				break;
//			case TURN:
//				speed = 0;
//				if( yaw says we've stopped)
//				{
//					turn = 50;
//					delay( 1000 );//wait for a bit while we reorient
//					while( !( sonar( FRONT ) > OBSTACLE_AVOIDANCE_THREASHOLD );
//					turn = 0;
//					speed = SPEED;
//					while( sonar( RIGHT ) > FOLLOW_WALL_SET_POINT );
//					state = FOLLOW_WALL;
//				}
//				break;
//			default:
//				break;
//		}
  }

int yaw()
{
	return 0;
}

