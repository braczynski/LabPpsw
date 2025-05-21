#include "../Library/led.h"
#include "../Library/keyboard.h"
#include "../Library/timer_interrupts.h"
#include "../library/servo.h"
#include "uart.h"

extern char cOdebranyZnak;

int main(){
	
	unsigned int iMainLoopCtr;
	unsigned int uiSerwoPosition = 0;
	
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
		
			switch(cOdebranyZnak) {
		
			case 'c':
			
				ServoCallib();
			
				cOdebranyZnak = 0; 
			break;
				
			case '1':
				
				uiSerwoPosition += 12;
				
				ServoGoTo(uiSerwoPosition);
				cOdebranyZnak = 0; 
			break;
			
			case '2':
				
				ServoGoTo(24);
				cOdebranyZnak = 0;
			break;
			
			case '3':
				
				ServoGoTo(36);
				cOdebranyZnak = 0;
			break;
			
			default:
				
				
			break;
		
		}
		
		iMainLoopCtr++;
	}
}
