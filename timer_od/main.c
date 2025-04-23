#include "../Library/led.h"
#include "../Library/keyboard.h"
#include "timer.h"

int main(){
	
	LedInit();
	KeyboardInit();
	InitTimer0Match0(500000);
	
	while(1) {
		LedStepRight();
		WaitOnTimer0Match0();
	}
}
