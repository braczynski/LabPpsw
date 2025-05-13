#include "../Library/led.h"
#include "../Library/keyboard.h"
#include "../Library/timer_interrupts.h"
#include "../library/servo.h"
#include "uart.h"

extern char cOdebranyZnak;

int main(){
	
	unsigned int iMainLoopCtr;
	unsigned int uiSerwoDegree = 0;
	
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
			
				uiSerwoDegree = 0;
				ServoCallib();
			break;
				
			case '1':
					
				uiSerwoDegree += 12;
				
				ServoGoTo(uiSerwoDegree);
			break;
			
			case '2':
				
				uiSerwoDegree = 24;
				ServoGoTo(24);
			break;
			
			case '3':
				
				uiSerwoDegree = 36;
				ServoGoTo(36);
			break;
			
			default:
				
				
			break;
		
		}
		
		cOdebranyZnak = 0; 
		iMainLoopCtr++;
	}
}
