#include <LPC21xx.H>
#include "led.h"

#define LED0_bm (1<<16)
#define LED1_bm (1<<17)
#define LED2_bm (1<<18)
#define LED3_bm (1<<19)

void LedInit(void) {
	
	IO1DIR |= (LED0_bm + LED1_bm + LED2_bm + LED3_bm);
}

void LedOn(unsigned char ucLedIndeks) {
	
		switch (ucLedIndeks) {
			case 0:
				IO1SET = LED0_bm;
				IO1CLR = (LED1_bm + LED2_bm + LED3_bm);
				break;
			case 1:
				IO1SET = LED1_bm;
				IO1CLR = (LED0_bm + LED2_bm + LED3_bm);
				break;
			case 2:
				IO1SET = LED2_bm;
				IO1CLR = (LED0_bm + LED1_bm + LED3_bm);
				break;
			case 3:
				IO1SET = LED3_bm;
				IO1CLR = (LED0_bm + LED1_bm + LED2_bm );
				break;
			default:
				IO1CLR = (LED0_bm + LED1_bm + LED2_bm + LED3_bm);
				break;
		}
}

enum Side{LEFT, RIGHT};

void eStep(enum Side side) {
	
	static unsigned int uiCurrentDiode = 0;

	if(side == LEFT) {
		LedOn(uiCurrentDiode%4);
	} else {
		LedOn(3 - (uiCurrentDiode%4));
	}
	
	uiCurrentDiode++;
}

void LedStepLeft(void) {
	
	eStep(LEFT);
}

void LedStepRight(void) {
	
	eStep(RIGHT);
}
