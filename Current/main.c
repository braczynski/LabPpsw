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
	
	enum LedState eLedState = LED_LEFT;
	unsigned char ucShiftCounter = 0;
	LedInit();
	
	while(1) {
	
		switch(eLedState) {
		
			case LED_LEFT:
				LedStepLeft();
			
				if(ucShiftCounter == 2) {
					
					eLedState = LED_RIGHT;
				}
			break;
		
			case LED_RIGHT:
				LedStepRight();
			
				if(ucShiftCounter == 5) {
					
					eLedState = LED_LEFT;
					ucShiftCounter = 0;
				}
			break;
		}
		
		ucShiftCounter++;
		Delay(250);
	}
}
