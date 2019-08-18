

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
    STOP,
    FORWARD,
    BACK,
    LEFT,
    RIGHT

} MOTOR_STATES;

static MOTOR_STATES motState = STOP; 

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

void updatefsm(unsigned int dat, int dist);
void stopState(MOTOR_STATES *motorState, unsigned int dat, int dist);
void forwardState(MOTOR_STATES *motorState, unsigned int dat, int dist);
void backwardState(MOTOR_STATES *motorState, unsigned int dat, int dist);
void leftState(MOTOR_STATES *motorState, unsigned int dat, int dist);
void rightState(MOTOR_STATES *motorState, unsigned int dat, int dist);

#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_STATE_H */

