#include "../Library/led.h"
#include "../Library/keyboard.h"
#include "timer.h"

int main(){
	
	LedInit();
	KeyboardInit();
	
	while(1) {
		LedStepLeft();
		InitTimer0Match0(500000);
		WaitOnTimer0Match0();
	}
}
