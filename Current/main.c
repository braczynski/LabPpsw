#include <LPC21xx.H>
// GPIO 15
#define MIL 5000
#define LED0_bm 0x10000
#define LED1_bm 0x20000
#define LED2_bm 0x40000
#define LED3_bm 0x80000

#define S0_bm 0X10

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
	
	IO1DIR |= LED0_bm + LED1_bm + LED2_bm + LED3_bm;
	
}

enum ButtonState {RELASED, PRESSED};

enum ButtonState ReadKeyboard1(){                                                      
	
	if((IO0PIN &= S0_bm) == S0_bm){
		return PRESSED;
	} else{
		return RELASED;
	}
}

void LedOn(unsigned char ucLedIndeks){
	
		IO1CLR |= LED0_bm + LED1_bm + LED2_bm + LED3_bm;
		
		switch (ucLedIndeks){
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

int main()
{

	LedInit();
	
	while(1)
	{
	
		if(ReadKeyboard1() == 1)
		{
			
			LedOn(1);
		} else{
			
			LedOn(0);
		}
		
	}
}
