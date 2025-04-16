#include "../Library/led.h"
#include "../Library/keyboard.h"

#define MilS 5000

void Delay(unsigned int uiTimeMs) {
	unsigned int uiCounter;
	
	for(uiCounter = 0; uiCounter < (MilS*uiTimeMs); uiCounter++) {
		// Petla opózniajaca
	}
}

enum LedState{STOP, LED_RIGHT};

int main(){
	
	enum LedState eLedState = LED_RIGHT;
	
	LedInit();
	KeyboardInit();
	
	while(1) {
	
		switch(eLedState) {
		
			case STOP:
				if( eKeyboardRead() == BUTTON_1) {
					
					eLedState = LED_RIGHT;
				} else {
					
					eLedState = STOP;
				}
			break;
		
			case LED_RIGHT:
				LedStepRight();
				
				if( eKeyboardRead() == BUTTON_0) {
					
					 eLedState = STOP;
				} else {
					
					eLedState = LED_RIGHT;
				}
			break;
		}
		
		Delay(100);
	}
}
