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
#include "jsmn.h" 
#include "uartFile.h"



int jsoneq(const char *json, jsmntok_t *tok, const char *s);

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
    
    createQueue(10);
    
    DRV_OC0_Enable();
    DRV_OC1_Enable();
 
    DRV_USART0_BaudSet(57600);
    //sendToUART("Begin");
    //vTaskDelay(pdMS_TO_TICKS(10000));
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{
    dbgOutputLoc(DLOC_TASKS);
    
    MOTOR_COMMAND motorCommand; 
    MOTOR_COMMAND *pMotorCommand; 
    //motorCommand.tick_right = 9;
    //motorCommand.location = 3;


    displacement = 0; 
    int temp; 
    int de1 = 0;
    printf("App-Task\n");
    while (1) 
    {
        if(xQueueReceive(xQueue, &(pMotorCommand),(TickType_t ) 50)){
            motorCommand = *pMotorCommand;
            dbgOutputLoc(DLOC_APP_AFTER_RECEIVE_QUEUE);
            
            if(motorCommand.location == 0){ // from UART thread 
                /*char temp[100];
                sprintf(temp, "motor location : %d , direction: %d , param: %d \n", motorCommand.location, motorCommand.direction, motorCommand.param);
                sendToUART(temp);*/
                
                if(motorCommand.direction == 1){ // f
                    if(motorCommand.param == -1){
                        updatefsm('f', NOCHANGE);
                    }
                    else{
                        updatefsm('f', motorCommand.param);
                    }
                    dbgOutputLoc(DLOC_APP_OP_FORWARD);
                }      
                else if(motorCommand.direction == 2){ //b
                    if(motorCommand.param == -1){
                        updatefsm('b', NOCHANGE);
                    }
                    else{
                        updatefsm('b', motorCommand.param);
                    }
                    dbgOutputLoc(DLOC_APP_OP_BACKWARD);
                }
                else if(motorCommand.direction == 3){ //l
                    if(motorCommand.param == -1){
                        updatefsm('l', NOCHANGE);
                    }
                    else{
                        updatefsm('l', motorCommand.param);
                    }
                    dbgOutputLoc(DLOC_APP_OP_LEFT);
                }
                else if(motorCommand.direction == 4){ //r
                    if(motorCommand.param == -1){
                        updatefsm('r', NOCHANGE);
                    }
                    else{
                        updatefsm('r', motorCommand.param);
                    }
                    dbgOutputLoc(DLOC_APP_OP_RIGHT);
                }
                else if(motorCommand.direction == 5){ //s
                    updatefsm('s', NOCHANGE);
                    dbgOutputLoc(DLOC_APP_OP_STOP);
                }
                else{
                    //**! ERROR 
                    updatefsm('s', NOCHANGE);
                }
            } // end if location == 0 -> UART Thread 
            else if(motorCommand.location == 1){ // from INT 
                displacement++;
                updatefsm('E', NOCHANGE); //continue   
                dbgOutputLoc(DLOC_APP_INT);
            }     
            
        } //end xqueue receive 
    } // end while 
    
    sendToUART("end App Tasks\n");
}//end App_Tasks 







/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void USART_Tasks ( void )
{
    char commStr [20] = "";
    unsigned int charComm;
    int distComm = NOCHANGE;
    char* bodyStr; 
    
    int displacement = 0; 
    int temp; 
    int de1 = 0;
    
    char opDef[50];
    char paramDef[10];
    
    int status = 1;
    char *message;
    //char distDef[10];
    
    int rovDist;
	int rovAngle; 
    
    char* outTemp = "";
	char out[200];

    
    const char *HttpRet = "HTTP/1.0 200 OK\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n%s";
    
    sendToUART("Starting USART.\r\n");
    while(1)
    {
        
        
        if(!DRV_USART0_ReceiverBufferIsEmpty()){
            dbgOutputLoc(DLOC_UART_BEFORE_READ_UART);
            unsigned int comm = DRV_USART0_ReadByte();
            //dbgUARTVal((char) (comm & 0xff));
            
            bodyStr = (char*)parseChar((char) (comm & 0xff));
            dbgOutputLoc(DLOC_UART_AFTER_READ_UART);
            //parseChar((char) (comm & 0xff));
            if(bodyStr != NULL){
                status =0;
              
                //it is finished parsing 
                int len = strlen(bodyStr);
                
                //sendToUART("DONE!!");
                
                jsmn_parser p;
                jsmntok_t t[128];

                jsmn_init(&p);
                int r = jsmn_parse(&p, bodyStr, strlen(bodyStr), t, sizeof(t) / sizeof(t[0])); //parse the body using jsmn/json 
                dbgOutputLoc(DLOC_UART_AFTER_JSMN_PARSE);
                if (r < 0) { //checks to make sure it was successful 
                    //printf("Failed to parse JSON: %d\n", r); //exit out - send error **! 
                    //sendToUART("FAILED TO PARSE JSON");
                    status = 1; 
                    message = "Failed to parse JSON";
                    //goto errorOut;
                    dbgOutputLoc(DLOC_UART_R_LESS_0);
                    continue;
                }
                if (r < 1 || t[0].type != JSMN_OBJECT) {
                    //printf("Object expected\n"); //exit out **! Send error 
                    //sendToUART("OBJECT EXPECTED");
                    //continue;
                    status = 1; 
                    message = "Object expected";
                    //goto errorOut;
                    dbgOutputLoc(DLOC_UART_NOT_JSMN_OBJ);
                    continue;
                }
                
                //clear all variables for parsing operations 
                opDef[0]='\0';
                paramDef[0] = '\0';
                
                int j = 0;
                for (; j < r-1; j++) {
                    //sendToUART("hello");
                    jsmntok_t key = t[j+1];
                    unsigned int length = key.end - key.start;
                    //printf("len=%d, S=%d, E=%d\n",length, key.start, key.end);
                    //strncpy(opDef,bodyStr+key.start, length);
                    //memcpy(opDef, bodyStr+key.start, length);
                    
                    
                    if (jsoneq(bodyStr, &t[j], "op") == 0) {
                        // We may use strndup() to fetch string value 
                        //printf("\nOP p=%p len=%d, S=%d, E=%d\n",bodyStr, length, key.start, key.end);
                        dbgOutputLoc(DLOC_UART_PARSE_OP);
                        int k =0;
                        for(; k<length; k++){
                            opDef[k] = *(bodyStr+(key.start+k));
                        }
//                        memcpy(opDef, bodyStr+key.start, length);
                        opDef[length] = '\0';
                        //char temp[20];
                        //sprintf(temp, "- Op: %s\n", opDef);
                        //sendToUART(temp);
                        j++;
                    }
                    else if (jsoneq(bodyStr, &t[j], "angle") == 0) {
                        //printf("\nangle p=%p len=%d, S=%d, E=%d\n",bodyStr, length, key.start, key.end);
                        dbgOutputLoc(DLOC_UART_PARSE_ANGLE);
                        int k =0;
                        for(; k<length; k++){
                            paramDef[k] = *(bodyStr+(key.start+k));
                        }
//                        memcpy(angleDef, bodyStr+key.start, length);
                        paramDef[length] = '\0';
                        //char temp[10]; 
                        rovAngle = atoi(paramDef);
                        if(rovAngle <= 0) rovAngle = -1;
                        //sprintf(temp, "- Angle: %i\n", rovAngle);
                        //sendToUART(temp);
                        j++;
                    }
                    else if (jsoneq(bodyStr, &t[j], "distance") == 0) {
                        dbgOutputLoc(DLOC_UART_PARSE_DIST);
                        int k =0;
                        // printf("distance p=%p len=%d, S=%d, E=%d\n",bodyStr, length, key.start, key.end);
                        for(; k<length; k++){
                            paramDef[k] = *(bodyStr+(key.start+k));
                        }
//                        memcpy(angleDef, bodyStr+key.start, length);
                        paramDef[length] = '\0';
                        //char temp[10];
                        rovDist = atoi(paramDef);
                        if(rovDist <= 0) rovDist = -1;
                        //sprintf(temp, "- Distance: %i\n", rovDist);
                        //sendToUART(temp);
                        j++;
                    }                    
                } //end for parser 
                
               
                BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
                if(strcmp(opDef, "forward") == 0){
                    dbgOutputLoc(DLOC_UART_OP_FORWARD);
                    MOTOR_COMMAND temp;
                    temp.location = 0; //UART thread 
                    temp.direction = 1; //
                    if(rovDist == -1){
                        temp.param = -1;
                    }
                    else{
                        temp.param = rovDist;
                    }
                    //printf("OP SECTION");
                    char tempstr[100];
                    sprintf(tempstr, "FORWARD motor location : %d , direction: %d , param: %d \n", temp.location, temp.direction, temp.param);
                    //sendToUART(tempstr);
                    //sendToUART("xxxxxxxxxxxxx");
                    
                    sendQueue(&temp, pxHigherPriorityTaskWoken);
                    dbgOutputLoc(DLOC_AFTER_QUEUE_SEND);
                }
                else if(strcmp(opDef, "backward") == 0){
                    dbgOutputLoc(DLOC_UART_OP_BACKWARD);
                    MOTOR_COMMAND temp;
                    temp.location = 0; //UART thread 
                    temp.direction = 2; //backward 
                    if(rovDist == -1){
                        temp.param = -1;
                    }
                    else{
                        temp.param = rovDist;
                    }
                    char tempstr[100];
                    sprintf(tempstr, "BACKWARD motor location : %d , direction: %d , param: %d \n", temp.location, temp.direction, temp.param);
                    //sendToUART(tempstr);
                    
                    sendQueue(&temp, pxHigherPriorityTaskWoken);
                    dbgOutputLoc(DLOC_AFTER_QUEUE_SEND);
                }
                else if(strcmp(opDef, "left") == 0){
                    dbgOutputLoc(DLOC_UART_OP_LEFT);
                    MOTOR_COMMAND temp;
                    temp.location = 0; //UART thread 
                    temp.direction = 3; //left
                    if(rovAngle == -1){
                        temp.param = -1;
                    }
                    else{
                        temp.param = rovAngle;
                    }
                    char tempstr[100];
                    sprintf(tempstr, "LEFT motor location : %d , direction: %d , param: %d \n", temp.location, temp.direction, temp.param);
                    
                    sendQueue(&temp, pxHigherPriorityTaskWoken);
                    dbgOutputLoc(DLOC_AFTER_QUEUE_SEND);
                }
                else if(strcmp(opDef, "right") == 0){
                    dbgOutputLoc(DLOC_UART_OP_RIGHT);
                    MOTOR_COMMAND temp;
                    temp.location = 0; //UART thread 
                    temp.direction = 4; //left
                    if(rovAngle == -1){
                        temp.param = -1;
                    }
                    else{
                        temp.param = rovAngle;
                    }
                    char tempstr[100];
                    sprintf(tempstr, "RIGHT motor location : %d , direction: %d , param: %d \n", temp.location, temp.direction, temp.param);
                    
                    sendQueue(&temp, pxHigherPriorityTaskWoken);
                    dbgOutputLoc(DLOC_AFTER_QUEUE_SEND);
                }
                else if(strcmp(opDef, "stop") == 0){
                    dbgOutputLoc(DLOC_UART_OP_STOP);
                    MOTOR_COMMAND temp;
                    temp.location = 0; //UART thread 
                    temp.direction = 5; //left
                    temp.param = -1;
                    
                    char tempstr[100];
                    sprintf(tempstr, "STOP motor location : %d , direction: %d , param: %d \n", temp.location, temp.direction, temp.param);
                    
                    sendQueue(&temp, pxHigherPriorityTaskWoken);
                    dbgOutputLoc(DLOC_AFTER_QUEUE_SEND);
                }
                else{
                    status = 1;
                    message = "Error: Operation not recognized";
                }
                

                if(0 == status){ //OKAY 
                    char sOut [1024];
                    char *pCh = "{\"Status\":\"Ok\"}";
                    //sprintf(sOut2,"{\"Status\":\"Ok\"}",opDef,paramDef);
                    len = strlen(pCh);
                    sprintf(sOut, HttpRet, len, pCh);
                    sendToUART(sOut);
                }
                else{ //NOT OKAY 
                    char sOut [1024];
                    char sOut2[100];
                    sprintf(sOut2,"{\"Status\":\"Fail\",\"message\",\"%s\"}",message);
                    len = strlen(sOut2);
                    sprintf(sOut, HttpRet, len, sOut2);
                    sendToUART(sOut);
                } //end else 
            } //end if bodystr!=null
        } //end if !USART empty 
    } //endwhile           
    
  sendToUART("End USART \n");
} //end function 


int jsoneq(const char *json, jsmntok_t *tok, const char *s) 
{
	if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start && strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}
    /*int direction; //1=F, 2=B, 3=L, 4=R, 5=S
    unsigned int distance; 
    unsigned int tick_left; //INT1
    unsigned int tick_right; //INT2
    int location; //1 = TestThread, 2 */

/*******************************************************************************
 End of File
 */
