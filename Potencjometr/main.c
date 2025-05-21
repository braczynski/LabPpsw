#include "adc.h"
#include "../Library/servo.h"
#include "../Library/Keyboard.h"

int main(){
	unsigned int iMainLoopCtr;
	
	ADC_Init();
	ADC_Start();
	
	KeyboardInit();
	ServoInit(50);
	
	while(1) {
		
			switch(eKeyboardRead()) {
		
			case BUTTON_0:
			
				ServoCallib();
			break;
				
			case BUTTON_1:
				
				ServoGoTo(12);
			break;
			
			case BUTTON_2:
				
				ServoGoTo(24);
			break;
			
			case BUTTON_3:
				
				ServoGoTo(36);
			break;
			
			default:
				
				
			break;
		
		}
		
		ServoGoTo(ADCServoValue());
		
		ADC_Start();
		iMainLoopCtr++;
	}
}
