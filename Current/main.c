#include "../Library/led.h"
#include "../Library/keyboard.h"
#include "../Library/timer_interrupts.h"

#include <LPC21xx.H>
#define DETECTOR_bm (1 << 10)

void DetectorInit() {
	
	IO0DIR &= ~(DETECTOR_bm);
}

enum DetectorState {ACTIVE, INACTIVE};

enum DetectorState eReadDetector() {
	
	if ((IO0PIN & DETECTOR_bm) == 0) {
		
		return ACTIVE;
	} else {
		
		return INACTIVE;
	}
}

void Automat() {
	enum LedState{STOP, LED_LEFT, LED_RIGHT, CALLIB};
	
	static enum LedState eLedState = CALLIB;
	
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
			
			case CALLIB:
				LedStepLeft();
				
				if( eReadDetector() == ACTIVE) {
					
					 eLedState = STOP;
				} else {
					
					eLedState = CALLIB;
				}
			break;
		}
}

int main(){
	
	unsigned int iMainLoopCtr;
	
	LedInit();
	KeyboardInit();
	DetectorInit();
	
	Timer0Interrupts_Init(20000, &Automat);
	while(1) {
		iMainLoopCtr++;
	}
}
