#include <LPC21xx.H> //GPIO 20
// LED
#define MIL 5000
#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000
//Button
#define S0_bm 0X10
#define S1_bm 0X40
#define S2_bm 0X20
#define S3_bm 0X80

#define allHigh_bm 0xFFFFFFFF

void delay(unsigned int uiTimeMs);
void LedInit(void);
void LedOn(unsigned char ucLedIndeks);

void delay(unsigned int uiTimeMs)
{
	unsigned int uiCounter;
	
	for(uiCounter = 0; uiCounter < (MIL*uiTimeMs); uiCounter++)
	{
	}
}

void LedInit(){
	
	IO1DIR |= (LED0_bm + LED1_bm + LED2_bm + LED3_bm);
	
}

void KeyboardInit() {
	unsigned int ihexMask;
	IO0DIR |= S0_bm + S1_bm + S2_bm + S3_bm;
	ihexMask = (allHigh_bm - (S0_bm + S1_bm + S2_bm + S3_bm));
	IO0DIR &= ihexMask;
}

enum KeyboardState {RELASED = 0, BUTTON_0 = 1, BUTTON_1 = 2, BUTTON_2 = 3, BUTTON_3 = 4};

enum KeyboardState eKeyboardRead() {
	
		if((IO0PIN & S0_bm) == 0){
			
			return BUTTON_0;
		} else if ((IO0PIN & S1_bm) == 0){
			
			return BUTTON_1;
		} else if((IO0PIN & S2_bm) == 0) {
			
			return BUTTON_2;
		} else if((IO0PIN & S3_bm) == 0) {
			
			return BUTTON_3;
		}else {
			
			return RELASED;
		}
}

void LedOn(unsigned char ucLedIndeks){
	
		switch (ucLedIndeks){
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

int main()
{

	LedInit();
	KeyboardInit();
	
	while(1)
	{
		
		switch (eKeyboardRead()){
			case BUTTON_0:
				LedOn(0);
				break;
			case BUTTON_1:
				LedOn(1);
				break;
			case BUTTON_2:
				LedOn(2);
				break;
			case BUTTON_3:
				LedOn(3);
				break;
			case RELASED:
				LedOn(4);
				break;
		}
		
	}
}
