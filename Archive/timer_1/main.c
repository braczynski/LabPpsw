#include "../Library/led.h"
#include "../Library/keyboard.h"
#include "timer.h"

int main(){
	
	LedInit();
	KeyboardInit();
	
	while(1) {
		LedStepLeft();
		WaitOnTimer0(1000);
	}
}
