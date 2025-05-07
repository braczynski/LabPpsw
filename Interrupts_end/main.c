#include "led.h"
#include "../Library/keyboard.h"
#include "timer_interrupts.h"

void Automat() {
	enum LedState{STOP, LED_LEFT, LED_RIGHT};
	
	static enum LedState eLedState = STOP;
	
		switch(eLedState) { //4
		
			case STOP:
				if( eKeyboardRead() == BUTTON_0) {
					
					eLedState = LED_LEFT;
				} else if(eKeyboardRead() == BUTTON_2){
					
					eLedState = LED_RIGHT;
				} else {
					
					eLedState = STOP;
				}
			break;
				
			case LED_LEFT:
				LedStepLeft();
				
				if( eKeyboardRead() == BUTTON_1) {
					 eLedState = STOP;
				} else {
					
					eLedState = LED_LEFT;
				}
			break;
		
			case LED_RIGHT:
				LedStepRight();
				
				if( eKeyboardRead() == BUTTON_1) {
					 eLedState = STOP;
				} else {
					
					eLedState = LED_RIGHT;
				}
			break;
			}
}

int main(){
	
	unsigned int iMainLoopCtr;
	
	LedInit();
	KeyboardInit();
	
	Timer0Interrupts_Init(20000, &Automat);
	while(1) {
		
		iMainLoopCtr++; //1
		iMainLoopCtr++;
		iMainLoopCtr++;
		iMainLoopCtr++; //6
		iMainLoopCtr++;
	}
}
