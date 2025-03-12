#include <LPC21xx.H>

#define MIL 5000
#define LED0_bm 0x10000

void delay(unsigned int time);

void delay(unsigned int uiTimeMs)
{
	unsigned int uiCounter;
	for(uiCounter = 0; uiCounter < (MIL*uiTimeMs); uiCounter++)
	{
	}
}

int main()
{
	IO1DIR = LED0_bm;
	
	while(1)
	{
		IO1SET |= LED0_bm;
		delay(50);
		IO1CLR |= LED0_bm;
		delay(50);
	}
}
