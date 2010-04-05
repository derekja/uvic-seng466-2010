/*
 * Control.cpp
 *
 *  Created on: Mar 25, 2010
 *      Author: jensweber
 */

#include "Control.h"

int newFanVal;
int newDirVal;
extern int fanVal;
extern int dirVal;
extern int dir;
extern int speed;
extern int turn;

//void control()
//{
//	while( true )
//	{
//		//set fan position
//		if ( fanPos < 750 )
//		{
//			newFanVal = map( fanPos, 120, 750, 0, 255 );
//			dir = 2;
//			newFanVal = 255 - newFanVal;
//		}
//
//		if ( fanPos > 800 )
//		{
//			newFanVal = map( fanPos, 800, 1023, 0, 255 );
//			dir = 1;
//		}
//
//		//set direction
//		if ( dirPos < 425 )
//		{
//			newDirVal = map( dirPos, 0, 450, 1000, 0 );
//			fanVal = ( fanVal * dirVal ) / 1000;
//		}
//
//		if ( dirPos > 500 )
//		{
//			newDirVal = map( dirPos, 500, 1023, 1000, 0 );
//			newFanVal = ( newFanVal * newDirVal ) / 1000;
//		}
//
//		//age old data
//		fanVal = ( ( fanVal * 2 ) / 3 ) + ( ( newFanVal * 1 ) / 3 );
//		dirVal = ( ( dirVal * 2 ) / 3 ) + ( ( newDirVal * 1 ) / 3 );
//
//		//wait for next call
//		task_next();
//	}
//}

void control() {
	const int STOP = 0;
	const int FOLLOW_WALL = 1;
	const int TURN = 2;
	const int AVOID_OBSTACLE = 3;
	const int FOLLOW_WALL_SET_POINT = 24;
	const int YAW_SET_POINT = 0;

	int follow_wall_prev_error;
	int follow_wall_error;
	int follow_wall_p;
	int follow_wall_kp = 8;
	int follow_wall_d;
	int follow_wall_kd = 4;
	int follow_wall_i;
	int follow_wall_ki = 2;
	int follow_wall_turn;

	int yaw_prev_error;
	int yaw_error;
	int yaw_p;
	int yaw_kp = 8;
	int yaw_d;
	int yaw_kd = 4;
	int yaw_i;
	int yaw_ki = 2;
	int yaw_turn;

	while (true) {
		switch (state) {
		case STOP:
			state = command;
			break;
		case FOLLOW_WALL:
			state = command;
			speed = SPEED;

			yaw_error = yaw() - YAW_SETPOINT;
			yaw_p = yaw_error;
			yaw_d = yaw_error - yaw_prev_error;
			yaw_i = (2 * yaw_old_error) / 3 + yaw_error / 3;
			yaw_prev_error = yaw_error;
			yaw_old_error = yaw_i;
			yaw_turn = (yaw_kp * yaw_p + yaw_kd * yaw_d + yaw_ki * yaw_i) / X;//that scaling factor of 1/X should keep the value between 100 and -100


			follow_wall_error = sonar() - FOLLOW_WALL_SET_POINT;
			follow_wall_p = follow_wall_error;
			follow_wall_d = follow_wall_error - follow_wall_prev_error;
			follow_wall_i = (2 * follow_wall_old_error) / 3 + follow_wall_error
					/ 3;
			follow_wall_prev_error = follow_wall_error;
			follow_wall_old_error = follow_wall_i;
			follow_wall_turn = (follow_wall_kp * follow_wall_p + follow_wall_kd
					* follow_wall_d + follow_wall_ki * follow_wall_i) / 3;//that scaling factor of 1/3 should keep the value between 100 and -100

			turn = (2 * yaw_turn + follow_wall_turn) / 3;

			break;
//		case TURN:
//			speed = 0;
//			if( yaw says we've stopped)
//			{
//				turn = 50;
//				delay(1000);//wait for a bit while we reorient
//				while( !( sonar( FRONT ) > OBSTACLE_AVOIDANCE_THREASHOLD ) {
//							turn = 0;
//							speed = SPEED;
//							while (sonar(RIGHT) > FOLLOW_WALL_SET_POINT)
//							;
//							state = FOLLOW_WALL;
//						}
//						break;
//					}
//				}
			}
		}
}
