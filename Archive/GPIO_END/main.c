#include <LPC21xx.H>

#define MilS 5000
// LED
#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000
//Button
#define S0_bm 0X10
#define S1_bm 0X40
#define S2_bm 0X20
#define S3_bm 0X80

void Delay(unsigned int uiTimeMs) {
	unsigned int uiCounter;
	
	for(uiCounter = 0; uiCounter < (MilS*uiTimeMs); uiCounter++) {
		// Petla opózniajaca
	}
}

void LedInit() {
	
	IO1DIR |= (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
}

void KeyboardInit() {
	
	IO0DIR &= ~(S0_bm | S1_bm | S2_bm | S3_bm);
}

enum KeyboardState {RELASED, BUTTON_0, BUTTON_1, BUTTON_2, BUTTON_3};

enum KeyboardState eKeyboardRead() {
	
		if((IO0PIN & S0_bm) == 0) {// PRESSED: 0x10 RELASED: 0
			
			return BUTTON_0;
		} else if ((IO0PIN & S1_bm) == 0) { //PRESSED: 0x40 RELASED: 0
			
			return BUTTON_1;
		} else if((IO0PIN & S2_bm) == 0) { //PRESSED: 0x20 RELASED: 0
			
			return BUTTON_2;
		} else if((IO0PIN & S3_bm) == 0) { //PRESSED: 0x80 RELASED: 0 
			
			return BUTTON_3;
		}else {
			
			return RELASED;
		}
}

void LedOn(unsigned char ucLedIndeks) {
		IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
	
		switch (ucLedIndeks) {
			case 0:
				IO1SET = LED0_bm;
				break;
			case 1:
				IO1SET = LED1_bm;
				break;
			case 2:
				IO1SET = LED2_bm;
				break;
			case 3:
				IO1SET = LED3_bm;
				break;
		}
}

enum Side{LEFT, RIGHT};

void eStep(enum Side side) {
	
	static unsigned char ucCurrentDiode = 0;

	if(side == LEFT) {
		ucCurrentDiode++;
	} else {
		ucCurrentDiode--;
	}
		
	LedOn(ucCurrentDiode%4);
}

void LedStepLeft(void) {
	
	eStep(LEFT);
}

void LedStepRight(void) {
	
	eStep(RIGHT);
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
