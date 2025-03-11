#include <LPC21xx.H>

void delay(void);

void delay(void)
{
	int i = 0;
	int j = 0;
	for(i = 0; i < 1000000000; i++)
	{
		j++;
	}
}

int main()
{
	int pin_16 = 0;
	pin_16 = 1 << 16; 
	IO1DIR = pin_16; /* 0x10000 */
	IO1SET = pin_16;
	IO1CLR = pin_16;
	
	while(1)
	{
		if(IO1SET == 0)
		{
			IO1SET=pin_16;
		} 
		else
		{
			IO1CLR = pin_16;
		}
		
		delay();
	}
}
