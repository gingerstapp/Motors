/* 
 * File:   debug.h
 * Author: Kelly Mak
 *
 * Created on June 20, 2019
 */

#ifndef DEBUG_H
#define	DEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif   
    
#include "system_definitions.h"
    
#define BEGIN_INIT_TASK (0x00)
#define DLOC_UART_ISR_BEGIN (0x01)
#define DLOC_INIT (0x02)
#define DLOC_TASKS (0x03)

//motor 
#define DLOC_FORWARD (0x10)
#define DLOC_BACK (0x12)
#define DLOC_LEFT (0x14)
#define DLOC_RIGHT (0x16)
#define DLOC_STOP (0x18)
#define DLOC_FORWARD_END (0x11)
#define DLOC_BACK_END (0x13)
#define DLOC_LEFT_END (0x15)
#define DLOC_RIGHT_END (0x17)
#define DLOC_STOP_END (0x19)
    
//queue
#define DLOC_QUEUE_CREATE (0x20)
#define DLOC_QUEUE_CREATE_FAIL (0x21)
#define DLOC_BEFORE_QUEUE_SEND (0x22)
#define DLOC_AFTER_QUEUE_SEND (0x23)
#define DLOC_QUEUE_FAIL_SEND (0x24)
#define DLOC_QUEUE_RECEIVE (0x25)
#define DLOC_QUEUE_WRITE (0x26)
#define DLOC_APP_BEFORE_RECEIVE_QUEUE (0x27)
#define DLOC_APP_AFTER_RECEIVE_QUEUE (0x28)
#define DLOC_QUEUE_SEND (0x29)
#define DLOC_QUEUE_RECEIVE_OUT (0x35)
    
//timer isr 
#define DLOC_TIMER_ISR_ENTER (0x30)
#define DLOC_TIMER_ISR_LEAVE (0x31)
#define DLOC_TIMER_ISR_BEFORE (0x32)
#define DLOC_TIMER_ISR_AFTER (0x33) 
    
#define DLOC_DEBUG_HALT (0x40)
#define DLOC_WHILE_LOOP (0x50)

//fsm 
#define DLOC_FSM_CHANGE (0x41)
#define DLOC_FSM_FORWARD (0x42)
#define DLOC_FSM_BACK (0x42)
#define DLOC_FSM_LEFT (0x44)
#define DLOC_FSM_RIGHT (0x45)
#define DLOC_FSM_STOP (0x46)
#define DLOC_FSM_DEFAULT (0x49)
    
//UART 
#define DLOC_APP_BEFORE_READ_UART (0x54)
#define DLOC_APP_AFTER_READ_UART (0x55)    
    
//ISR - INT1 
#define DLOC_INT1_ISR_ENTER (0x51)
#define DLOC_INT1_ISR_LEAVE (0x52)

// ISR - INT 2
#define DLOC_INT2_ISR_ENTER (0x61)
#define DLOC_INT2_ISR_LEAVE (0x62) 
    
#define test1 (0x63)
#define test2 (0x64)
#define test3 (0x65)
    
void dbgOutputVal(unsigned int outVal);
void dbgUARTVal(unsigned char outVal);
void dbgOutputLoc(unsigned int outVal);
void halt();


#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */

