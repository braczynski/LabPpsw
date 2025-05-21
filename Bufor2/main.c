#include "uart.h"
#include "../Library/keyboard.h"
#include "../Library/timer_interrupts.h"
#include "../library/servo.h"
#include "string.h"
#include "command_decoder.h"

#define TERMINATOR '\0'

int main(){
	
	unsigned int iMainLoopCtr;
	char cString[RECIEVER_SIZE];
	
	KeyboardInit();
	DetectorInit();
	UART_InitWithInt(9600);
	
	ServoInit(50);
	
	while(1) {
		
			switch(eKeyboardRead()) {
		
			case BUTTON_0:
			
				ServoCallib();
			break;
				
			case BUTTON_1:
				
				ServoGoTo(12);
			break;
			
			case BUTTON_2:
				
				ServoGoTo(24);
			break;
			
			case BUTTON_3:
				
				ServoGoTo(36);
			break;
			
			default:
				
				
			break;
		
			}
		
		if(eReciever_GetStatus() == READY) {
			
			Reciever_GetStringCopy(cString);
			
			DecodeMsg(cString);
			
			if((0 != ucTokenNr) || (asToken[0].eType == KEYWORD)) {
				
				switch (asToken[0].uValue.eKeyword) {
				
				case CAL:
					
					ServoCallib();
				break;
					
				case GT:
				
				ServoGoTo(asToken[1].uValue.uiNumber);
				break;
				
				} 
			}
		}
		
		
		iMainLoopCtr++;
	}
}
