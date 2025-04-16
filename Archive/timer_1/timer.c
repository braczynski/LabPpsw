#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE_bm 0x1
#define COUNTER_RESET_bm 0x2

void InitTimer0(void) {
	
	T0TCR = COUNTER_ENABLE_bm;
}

void WaitOnTimer0(unsigned int uiTime) {
	
	InitTimer0();
	
	while((uiTime*15000) >= T0TC) {
		
	}
	
	T0TCR = COUNTER_RESET_bm;
	T0TC = 0;
	
}
