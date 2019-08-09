/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"
#include "debug.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

#include "app.h"

// Initialization of Ports, Queues
void APP_Initialize ( void )
{
    //initialize pins for dbgOutput
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, 0x00FF);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, 0x00FF);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_C, 0x00FF);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_G, 0x00FF);
    
    dbgOutputLoc(BEGIN_INIT_TASK);
    
    //initialize drivers
    DRV_TMR0_Start();
//    DRV_USART0_Initialize(); i don't think we need 
    /*DRV_ADC_Open();
    DRV_ADC_Start(); */ 
    
    createQueue();
    INT1COUNT = 0;
    INT2COUNT = 0;
    
    DRV_OC0_Enable();
    DRV_OC1_Enable();
    
  //  PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, 0x21);
    
    
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    //initialize for state machine
    //SENSOR_DATA currState;
    //currState.state = STATE1;
    dbgOutputLoc(DLOC_TASKS);
    
    MOTOR_COMMAND motorCommand; 
    MOTOR_DATA motDat; 
    motDat.state = CHANGE;
    
    while (1) 
    {
        
        dbgOutputLoc(DLOC_WHILE_LOOP);
        
        dbgOutputLoc(DLOC_APP_BEFORE_RECEIVE_QUEUE);
        motorCommand = readQueue();
        dbgOutputLoc(DLOC_APP_AFTER_RECEIVE_QUEUE);
        
        /*vTaskDelay(pdMS_TO_TICKS(1000));
        turnleft(); //how to test code 
        vTaskDelay(pdMS_TO_TICKS(1000));
        turnright();
        vTaskDelay(pdMS_TO_TICKS(2000)); */
        
       /*  Ignore this since we're not doing encoders 
        * if(motorCommand.location == 0){ // test thread 
            
        }
        else if(motorCommand.location == 1){ // INT1
            //ticksleft
        }
        else if(motorCommand.location == 2){ //INT2 
            //ticksright 
        }
        else{
            
        }*/
            
        //motDat = updatefsm(motDat, motorCommand);
        
        
        //vTaskDelay(pdMS_TO_TICKS(1000));
        
    }
}

    /*int direction; //1=F, 2=B, 3=L, 4=R, 5=S
    unsigned int distance; 
    unsigned int tick_left; //INT1
    unsigned int tick_right; //INT2
    int location; //1 = TestThread, 2 */

/*******************************************************************************
 End of File
 */
