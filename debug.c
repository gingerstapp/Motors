#include "debug.h"

void dbgOutputVal(unsigned int outVal)
{
    outVal = outVal & 0x7F;  //mask so we only have the last seven bits
    //PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_D, 7); //toggle indicator bit
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_D, outVal);
}

void dbgUARTVal(unsigned char outVal)
{
    DRV_USART0_WriteByte(outVal); 
}

void dbgOutputLoc(unsigned int outVal)
{
    outVal = outVal & 0x7F; //mask for last 7
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, outVal);
    //PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_E, 7);
}

void halt()
{
    dbgOutputLoc(DLOC_DEBUG_HALT);
    vTaskSuspendAll();
    PLIB_INT_Disable(TMR_ID_2);
    while(1)
    {
        //infinite loop
    }
}

