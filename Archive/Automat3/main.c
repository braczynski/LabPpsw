#include "../Library/led.h"
#include "../Library/keyboard.h"

#define MilS 5000

void Delay(unsigned int uiTimeMs) {
	unsigned int uiCounter;
	
	for(uiCounter = 0; uiCounter < (MilS*uiTimeMs); uiCounter++) {
		// Petla opózniajaca
	}
}

enum LedState{LED_LEFT, LED_RIGHT};

int main(){
	
	enum LedState eLedState = LED_RIGHT;
	unsigned char ucShiftCounter = 0;
	
	LedInit();
	KeyboardInit();
	
	while(1) {
	
		switch(eLedState) {
			
			case LED_LEFT:
				LedStepLeft();
				
				if( ucShiftCounter == 6) {
					
					 eLedState = LED_RIGHT;
					ucShiftCounter = 0;
				} else {
					
					eLedState = LED_LEFT;
				}
			break;
		
			case LED_RIGHT:
				LedStepRight();
				
				if( ucShiftCounter == 3) {
					
					 eLedState = LED_LEFT;
				} else {
					
					eLedState = LED_RIGHT;
				}
			break;
		}
		
		ucShiftCounter++;
		
		Delay(500);
	}
}
