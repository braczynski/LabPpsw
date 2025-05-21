#include "../Library/led.h"
#include "../Library/keyboard.h"
#include "../Library/timer_interrupts.h"
#include "servo.h"

int main(){
	
	unsigned int iMainLoopCtr;
	
	KeyboardInit();
	DetectorInit();
	ServoInit(50);
	
	ServoGoTo(24);
	ServoGoTo(12);
	
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
		iMainLoopCtr++;
	}
}
