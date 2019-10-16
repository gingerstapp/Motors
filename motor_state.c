
//#include "system/common/sys_buffer.h"
#include "motor_state.h"

int displacement = 0;

void updatefsm(unsigned int dat, int param){
    if (dat == 'E') {  // ENter existing state - no update
        
        switch(motState){
            case STOP:
                dbgOutputLoc(DLOC_STATE_STOP);
                stopState(&motState, dat, param);
                break;
            case FORWARD: 
                dbgOutputLoc(DLOC_STATE_FORWARD);            
                forwardState(&motState, dat, param);
                break;
            case BACK:
                dbgOutputLoc(DLOC_STATE_BACKWARD);
                backwardState(&motState, dat, param);
                break;
            case LEFT:
                dbgOutputLoc(DLOC_STATE_LEFT);
                leftState(&motState, dat, param);
                break;
            case RIGHT:
                dbgOutputLoc(DLOC_STATE_RIGHT);
                rightState(&motState, dat, param);
                break;
            default:
                dbgOutputLoc(DLOC_FSM_DEFAULT);
                halt();
                break;
        }
    }
    else { //change state 
        //dbgUARTVal('C');
        //dbgUARTVal(dat );
        switch(dat){
            case 'f':
                motState = FORWARD;
                forwardState(&motState, dat, param);
                break;
            case 'b':
                motState = BACK;
                backwardState(&motState, dat, param);
                break;
            case 'l':
                motState = LEFT;
                leftState(&motState, dat, param);
                break;
            case 'r':
                motState = RIGHT;
                rightState(&motState, dat, param);
                break;
            case 's':
                //stay in Neutral 
                motState = STOP;
                stopState(&motState, dat, param);
                //stop();
                break;
            default:
                //stop();

                break;
        }


    }
   
}


void stopState(MOTOR_STATES *motorState, unsigned int dat, int dist){
    stop();
}
    
void forwardState(MOTOR_STATES *motorState, unsigned int dat, int param){
    static int in_Dist = 0;
    if (dat == 'f') {
        goforward();
        in_Dist = param;
        displacement = 0;
    }     
    
    if(in_Dist >= -1 && displacement >= in_Dist){
        //dbgUARTVal('F');
        displacement = 0;
        in_Dist = -1;
        *motorState = STOP;
    }
   
}

void backwardState(MOTOR_STATES *motorState, unsigned int dat, int param){
    static int in_Dist = 0;
    if (dat == 'b') {
        gobackward();
        in_Dist = param;
        displacement = 0;
    }
    if(in_Dist >= -1 && displacement >= in_Dist){
        displacement = 0;
        in_Dist = -1;
        *motorState = STOP;
    }
}

void leftState(MOTOR_STATES *motorState, unsigned int dat, int param){
    turnleft();
    //vTaskDelay(pdMS_TO_TICKS(2000));
    
    *motorState = STOP;
    //unsigned int data = 's';
    //stopState(motState, data, dist);
}
void rightState(MOTOR_STATES *motorState, unsigned int dat, int param){ 
    turnright();
    //vTaskDelay(pdMS_TO_TICKS(1550));
    *motorState = STOP;
    //unsigned int data = 's';
    //stopState(motState, data, dist);
}