#include "../Library/led.h"
#include "../Library/keyboard.h"

#define MilS 5000

void Delay(unsigned int uiTimeMs) {
	unsigned int uiCounter;
	
	for(uiCounter = 0; uiCounter < (MilS*uiTimeMs); uiCounter++) {
		// Petla opózniajaca
	}
}

enum LedState{STOP, LED_LEFT, LED_RIGHT, BLINKING, STANDBY};

int main(){
	
	unsigned char ucBlinkCounter = 0;
	enum LedState eLedState = STOP;
	
	LedInit();
	KeyboardInit();
	
	while(1) {
	
		switch(eLedState) {
		
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
				
				if( eKeyboardRead() == BUTTON_1) {
					
					 eLedState = STOP;
				} else {
					
					LedStepLeft();
					eLedState = LED_LEFT;
				}
			break;
		
			case LED_RIGHT:
				
				if( eKeyboardRead() == BUTTON_1) {
					
					 eLedState = STOP;
				} else if(eKeyboardRead() == BUTTON_3) {
					
					eLedState = BLINKING;
				} else {
					
					LedStepRight();
					eLedState = LED_RIGHT;
				}
			break;
				
			case BLINKING:
				
				if( ucBlinkCounter == 5) {
						ucBlinkCounter = 0;
						eLedState = STANDBY;
				} else {
					
					ucBlinkCounter++;
					
					if( (ucBlinkCounter % 2) == 0) {
						
						LedOn(3);
					} else {
				
						LedOn(4);
					}
					
					eLedState = BLINKING;
				}
			break;
				
			case STANDBY:
				
				if( eKeyboardRead() == BUTTON_1) {
					
					eLedState = LED_LEFT;
				} else {
					
					eLedState = STANDBY;
				}
				
			break;
		}
		
		Delay(100);
	}
}
