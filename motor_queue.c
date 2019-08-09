#include "motor_queue.h"

void sendQueue(MOTOR_COMMAND sendValue, BaseType_t pxHigherPriorityTaskWoken) {
    MOTOR_COMMAND buffer = sendValue;
    if (pdPASS != xQueueSendFromISR(xQueue, &buffer, &pxHigherPriorityTaskWoken)) {
        dbgOutputLoc(DLOC_QUEUE_FAIL_SEND);
    }
    else {
        dbgOutputLoc(DLOC_QUEUE_SEND);
    }
}

MOTOR_COMMAND readQueue(void) {
    dbgOutputLoc(DLOC_QUEUE_RECEIVE);
    MOTOR_COMMAND value;
    //block until value in queue to be read
    //don't need to check if read value received because of this setting
    xQueueReceive(xQueue, &value, portMAX_DELAY);
    return value;
}

void createQueue(void)
{
    dbgOutputLoc(DLOC_QUEUE_CREATE);
    xQueue = xQueueCreate(10, sizeof(unsigned int));
    if (xQueue == NULL) {
        dbgOutputLoc(DLOC_QUEUE_CREATE_FAIL);
        halt();
    }
}