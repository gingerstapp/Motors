

#ifndef MOTOR_QUEUE_H
#define	MOTOR_QUEUE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include "debug.h"
#include "queue.h"
#include "motor.h"
#include "app.h"
    
    
typedef struct{
        // may need to change this based on package to server 
    int direction; //1=F, 2=B, 3=L, 4=R, 5=S
    unsigned int distance; 
    unsigned int tick_left; //INT1
    unsigned int tick_right; //INT2
    int location; //1 = TestThread, 2 = INT1, 3 = INT2
} MOTOR_COMMAND;
    //void sendQueue(unsigned int sendValue, BaseType_t pxHigherPriorityTaskWoken);
    //unsigned int readQueue(void);
    void sendQueue(MOTOR_COMMAND *sendValue, BaseType_t pxHigherPriorityTaskWoken);
    MOTOR_COMMAND readQueue(void);
    void createQueue(int size);
    
    
    QueueHandle_t xQueue;


#ifdef	__cplusplus
}
#endif

#endif	/* SENSOR_QUEUE_H */

