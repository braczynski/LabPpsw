#include "keyboard.h"
#include "led.h"

#define MilS 5000

void Delay(unsigned int uiTimeMs) {
	unsigned int uiCounter;
	
	for(uiCounter = 0; uiCounter < (MilS*uiTimeMs); uiCounter++) {
		// Petla opózniajaca
	}
}

int main() {;

	LedInit();
	KeyboardInit();
	
	while(1)
	{
		
		Delay(50);
		
		switch (eKeyboardRead()) {
			case BUTTON_1:
				LedStepRight();
				break;
			case BUTTON_2:
				LedStepLeft();
				break;
			default:
				break;
		}
		
		Delay(50);
	}
}
