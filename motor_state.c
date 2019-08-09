
//#include "system/common/sys_buffer.h"
#include "motor_state.h"

MOTOR_DATA updatefsm(MOTOR_DATA motdat,unsigned int changeMotor){
    switch(motdat.state){
        case CHANGE:
            
            //Forward = 1, Back = 2, Left = 3, Right = 3, Stop = 5
            switch(changeMotor){
                case 1: 
                    motdat.state = FORWARD;
                    break;
                case 2:
                    motdat.state = BACK;
                    break;
                case 3: 
                    motdat.state = LEFT;
                    break;
                case 4: 
                    motdat.state = RIGHT;
                    break;
                case 5: 
                    motdat.state = STOP;
                    break;
            }
            break;
        case FORWARD: 
            goforward();
            
            
            break;
        case BACK:
            gobackward();
            
            break;
        case LEFT:
            turnleft();
            
            motdat.state = CHANGE;
            
            break;
        case RIGHT:
            turnright();
            
            motdat.state = CHANGE;
            break;
        case STOP:
            stop();
            
            break;
        default:
            dbgOutputLoc(DLOC_FSM_DEFAULT);
            halt();
            break;

    }
    return motdat;
    
}