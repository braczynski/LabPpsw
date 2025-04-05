#include "keyboard.h"
#include "led.h"

#define MilS 5000

void Delay(unsigned int uiTimeMs) {
	unsigned int uiCounter;
	
	for(uiCounter = 0; uiCounter < (MilS*uiTimeMs); uiCounter++) {
		// Petla opózniajaca
	}
}

int main() {
	
	unsigned char ucStepCounter = 1;

	LedInit();
	KeyboardInit();
	
	while(1)
	{
		
		Delay(50);
		
		if (ucStepCounter <= 9) {
				LedStepRight();
		} else if (ucStepCounter <= 18) {
				LedStepLeft();
		} else {
			ucStepCounter = 1;
		}
		ucStepCounter++;
		Delay(50);
	}
}