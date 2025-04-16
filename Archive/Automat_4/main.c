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
	
	enum LedState eLedState = STOP;
	unsigned char ucShiftCounter = 0;
	
	LedInit();
	KeyboardInit();
	
	while(1) {
	
		switch(eLedState) {
		
			case STOP:
				if( eKeyboardRead() == BUTTON_0) {
					
					eLedState = LED_RIGHT;
					
					ucShiftCounter = 0;
				} else {
					
					eLedState = STOP;
				}
			break;
		
			case LED_RIGHT:
				LedStepRight();
				
				if( ucShiftCounter == 3) {
					
					 eLedState = STOP;
				} else {
					
					eLedState = LED_RIGHT;
				}
			break;
		}
		
		ucShiftCounter++;
		
		Delay(100);
	}
}
