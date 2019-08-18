/*******************************************************************************
 System Interrupts File

  File Name:
    system_interrupt.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

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

#include "system/common/sys_common.h"
#include "app.h"
#include "system_definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************
static int int1count = 0; 
static int int2count = 0; 


void IntHandlerExternalInterruptInstance0(void)
{
    //you can ignore this since we're not doing encoders 
    
    
    //Pin 2, Interrupt 1 
    //dbgOutputLoc(DLOC_INT1_ISR_ENTER);
    /*INT1COUNT++;
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    
    MOTOR_COMMAND temp; 
    temp.location = 2; 
    temp.tick_left = INT1COUNT;
    
    if(INT1COUNT == 100){        
        dbgOutputLoc(DLOC_BEFORE_QUEUE_SEND);
        sendQueue(temp, pxHigherPriorityTaskWoken);
        dbgOutputLoc(DLOC_AFTER_QUEUE_SEND);
    }
    */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_1);
   // dbgOutputLoc(DLOC_INT1_ISR_LEAVE);
}
void IntHandlerExternalInterruptInstance1(void)
{
    //you can ignore this since we're not doing encoders 
    
    //Pin 7, Interrupt 2 
    dbgOutputLoc(DLOC_INT2_ISR_ENTER);
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    static int inc1 = 0;
    
    /*if(fb == 1)    
        int2count++;
    else if (fb == 2)
        int2count--;*/
    
    /*MOTOR_COMMAND temp;
    temp.location = 3;
    temp.tick_right = int2count;*/
    
    int2count++;
    
    MOTOR_COMMAND temp;
    temp.location = 1;
    temp.tick_right = inc1;
    
    

    //dbgUARTVal(9);
    //DRV_USART0_WriteByte(9); 
    //dbgOutputLoc(test3);
    
    if(int2count >= 70){
//        dbgOutputLoc(DLOC_BEFORE_QUEUE_SEND);
        sendQueue(&temp, pxHigherPriorityTaskWoken);
        dbgOutputLoc(DLOC_AFTER_QUEUE_SEND);
        int2count = 0; 
        inc1++;
        
    } else {
        dbgOutputLoc(DLOC_INT2_ISR_LEAVE);
    }
    
    
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_2);
     
    
}
 

void IntHandlerDrvTmrInstance0(void)
{
    //dbgOutputLoc(DLOC_TIMER_ISR_ENTER);
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    
    /*MOTOR_COMMAND temp;
    temp.location = 1;
    temp.tick_right = 9;
       
    dbgOutputLoc(DLOC_BEFORE_QUEUE_SEND);
    sendQueue(temp, pxHigherPriorityTaskWoken);
    dbgOutputLoc(DLOC_AFTER_QUEUE_SEND);
    */
     
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_3);
    //dbgOutputLoc(DLOC_TIMER_ISR_LEAVE);
}

/*******************************************************************************
 End of File
*/
