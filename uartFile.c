#include "uartFile.h"

char inBuffer[10];
int inBufLen = 0;
char inHeader[1024];
int inHdrLen = 0;
char inBody[100];
int inBodyLen = 0;
const char *httpOpen = "*OPEN*";
const char *httpClose = "*CLOS*";
const char *httpContentLen = "Content-Length:";

int ContentLen = -1;

enum httpState { wait, openCheck, open, header, body };

enum httpState State = wait;
    


void sendToUART(char* str){
    size_t length = strlen(str);
    size_t i = 0;
    for(; i < length; i++){
        dbgUARTVal(str[i]);
    }
}

//const char *TestStr1 = "\r\n*OPEN*POST / HTTP/1.1\r\nHost: 192.168.1.30\r\nContent-Length: 31\r\nContent-Type: application/json\r\n\r\n{\"Op\": \"right\", \"angle\": \"10\" }*CLOS*";
//const char *TestJSONStr1 = "{\"Op\": \"right\", \"angle\": \"10\", \"distance\": \"50\"}";


void UartReset()
{
	State = wait;
	inBufLen = 0;
	inHdrLen = 0;
	inBodyLen = 0;
	ContentLen = -1;
	memset(inBuffer, 0, 10);
	memset(inHeader, 0, 1024);
	//memset(inBody, 0, BUFFER_SIZE);
}


char* parseChar(char ch) {
	switch (State) {
	case wait:  // tring to get *Open*
		if (ch == '*') State = openCheck;
		inBuffer[0] = ch;
		inBufLen = 1;
		break;
	case openCheck:
		inBuffer[inBufLen++] = ch;
		if (inBufLen >= 6) {
			if (strncmp(inBuffer, httpOpen, 6) == 0) {
				State = header;
				memset(inHeader, 0, 1024);
				inHdrLen = 0;
			}
			else {
				State = wait;
				inBufLen = 0;
			}
		}
		else {
			if (ch == '*') {  // case with **OPEN or anything before *OPEN* then we reset back to 
				inBufLen = 1;
			}
		}
		break;
	case header: // Check until \r\n\r\n
		inHeader[inHdrLen++] = ch;
		// checck if last 4 char is "\r\n\r\n"
		if (inHdrLen > 30) {
			if (strncmp("\r\n\r\n", (inHeader + (inHdrLen - 4)), 4) == 0) {
				// End of header reached - parse header
				// Get Content-Length
				char *ptr = strstr(inHeader, httpContentLen);  // Find "Content-Length:"
				if (ptr != NULL) {
					char *end = strstr(ptr + strlen(httpContentLen), "\r\n");  //Content-Length: 31[\r\n]
					*end = '\0';
					ContentLen = -1;
					if (end != NULL) {
						ContentLen = atoi(ptr + strlen(httpContentLen));
					}
				}
				if (ContentLen <= 0) {
					// no meaningful data - back to wait or disconnect Wifly connection session
					State = wait;
					return NULL;
				}

				State = body;
				// Clean up in boddy buffer
				memset(inBody, 0, 100);
				inBodyLen = 0;
			}
		}
		break;
	case body: // Read time Content-Length specific
		inBody[inBodyLen++] = ch;
		if (inBodyLen >= ContentLen) {
			State = wait;
			//printf("we got it all\n%s\n", inBody);
			// Do the operation here - process is just 
			//.......
			inBody[inBodyLen] = '\0';  // terminate the body string
									   //char* tempParsed = inBody;
			
			UartReset();
			return inBody;

		}
		break;

	default:
		break;
	}
	return NULL;
}

