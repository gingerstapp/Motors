#include "motor.h"

void turnleft(){
    dbgOutputLoc(DLOC_LEFT);
    //DIR1 C14 0, EN1 D0 1, DIR2 G1 1, EN2 D1 1
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, 0);
    SYS_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_C, 14);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, 1);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, 1);
    
    
    vTaskDelay(pdMS_TO_TICKS(1750));
    dbgOutputLoc(DLOC_LEFT_END);
    stop();
}

void turnright(){
    dbgOutputLoc(DLOC_RIGHT);
    //DIR1 C14 1, EN1 D0 1, DIR2 G1 0, EN2 D1 1
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, 0);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, 1);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, 14);
    SYS_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_G, 1);
    
    vTaskDelay(pdMS_TO_TICKS(1450));
    
    dbgOutputLoc(DLOC_RIGHT_END);
    stop();
}

void goforward(){ //parameters is distance 
    dbgOutputLoc(DLOC_FORWARD);
    
    //DIR1 C14 0, EN1 D0 1, DIR2 G1 0, EN2 D1 1
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, 0);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, 1);
    SYS_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_C, 14);
    SYS_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_G, 1);
    
}

void gobackward(){ //parameters is distance 
    dbgOutputLoc(DLOC_BACK);
    
    //DIR1 C14 1, EN1 D0 1, DIR2 G1 1, EN2 D1 1
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, 0);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, 1);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, 14);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, 1);
    
    dbgOutputLoc(DLOC_BACK_END);
}
void stop(){
    dbgOutputLoc(DLOC_STOP);
    
    SYS_PORTS_Set(PORTS_ID_0, PORT_CHANNEL_G, 1, 1);
    
    //DIR1 C14 0, EN1 D0 0, DIR2 G1 0, EN2 D1 0
    SYS_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_D, 0);
    SYS_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_D, 1);
    SYS_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_C, 14);
    SYS_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_G, 1);
    
    dbgOutputLoc(DLOC_STOP_END);
}