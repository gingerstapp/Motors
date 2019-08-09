

#ifndef MOTOR_STATE_H
#define	MOTOR_STATE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "debug.h"   
#include <stdio.h>
    
typedef enum
{
	/* Application's state machine's initial state. */
    CHANGE,
    FORWARD,
    BACK,
    LEFT,
    RIGHT,
    STOP

} MOTOR_STATES;

typedef struct
{
    /* The motor's current state */
    MOTOR_STATES state;
    //unsigned int distance; 
    //ticks_left, ticks_right, location (0=test thread, 1 = ext int1[ticks+left], 2 = ext int2[ticks_right]), direction, distance -> for Motor message queue 
    //send ticks to queue from interrupts 
    
    //state machine: when done=1, move to next state 
    //state machine: read command, do it, done, repeat 

} MOTOR_DATA;

MOTOR_DATA updatefsm(MOTOR_DATA motdat,unsigned int changeMotor);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_STATE_H */

