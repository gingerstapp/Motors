#include "motor_queue.h"

void sendQueue(MOTOR_COMMAND *sendValue, BaseType_t pxHigherPriorityTaskWoken) { //MOTOR_COMMAND sendValue, BaseType_t pxHigherPriorityTaskWoken) {
    MOTOR_COMMAND *buffer = sendValue;
    //unsigned int buffer = sendValue;
//    if (pdPASS != xQueueSendFromISR(xQueue, &buffer, &pxHigherPriorityTaskWoken)) {
    if (pdPASS != xQueueSendFromISR(xQueue, sendValue, &pxHigherPriorityTaskWoken)) {
        dbgOutputLoc(DLOC_QUEUE_FAIL_SEND);
    }
    else {
        dbgOutputLoc(DLOC_QUEUE_SEND);
    }
}

MOTOR_COMMAND readQueue(void) {
//unsigned int readQueue(void){
    dbgOutputLoc(DLOC_QUEUE_RECEIVE);
    MOTOR_COMMAND value;
    //unsigned int value;
    //block until value in queue to be read
    //don't need to check if read value received because of this setting
    xQueueReceive(xQueue, &value, portMAX_DELAY);
    return value;
    dbgOutputLoc(DLOC_QUEUE_RECEIVE_OUT);
}

void createQueue(int size)
{
    dbgOutputLoc(DLOC_QUEUE_CREATE);
    xQueue = xQueueCreate(size, sizeof(MOTOR_COMMAND));
    if (xQueue == NULL) {
        dbgOutputLoc(DLOC_QUEUE_CREATE_FAIL);
        halt();
    }
}