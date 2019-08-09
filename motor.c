#include "motor.h"

void motor(){
    //pins : 
    /*
     * RD0 - EN1 
        RD1 - EN2 
        RC14 - Direction 1 (M1) 
        RG1  Direction 2 

     */
    //enable: 
    
    //OC: 
    
    //direction: 
    
    
}

void turnleft(){
    dbgOutputLoc(DLOC_LEFT);
    //DIR1 C14 0, EN1 D0 1, DIR2 G1 1, EN2 D1 1
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, 0);
    SYS_PORTS_PinClear (PORTS_ID_0, PORT_CHANNEL_C, 14);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, 1);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, 1);
    
    vTaskDelay(pdMS_TO_TICKS(150));
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
    
    vTaskDelay(pdMS_TO_TICKS(150));
    
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
    
    

    dbgOutputLoc(DLOC_FORWARD_END);
}

void gobackward(){ //parameters is distance 
    dbgOutputLoc(DLOC_BACK);
    
    //DIR1 C14 1, EN1 D0 1, DIR2 G1 1, EN2 D1 1
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, 0);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_D, 1);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_C, 14);
    SYS_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_G, 1);
    
   /* SYS_PORTS_Set(PORTS_ID_0, PORT_CHANNEL_D, 1, 0);
    SYS_PORTS_Set(PORTS_ID_0, PORT_CHANNEL_D, 1, 1);
    SYS_PORTS_Set(PORTS_ID_0, PORT_CHANNEL_C, 1, 14);
    SYS_PORTS_Set(PORTS_ID_0, PORT_CHANNEL_G, 1, 1);*/
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