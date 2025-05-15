#include "uart.h"
#include "../Library/keyboard.h"
#include "../Library/timer_interrupts.h"
#include "../library/servo.h"
#include "../library/lancuchy_PO.h"

#define TERMINATOR '\0'

int main(){
	
	unsigned int iMainLoopCtr;
	char cString[20];
	
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
			
			if(eCompareString(cString, "callib")) {
				
				ServoCallib();
			} else if(eCompareString(cString, "left")) {
				
				ServoGoToInDegree(90);
			} else if(eCompareString(cString, "right")) {
				
				ServoGoToInDegree(270);
			}
		}
		
		
		iMainLoopCtr++;
	}
}
