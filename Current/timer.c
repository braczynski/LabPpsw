#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE_bm (1 << 0)
#define COUNTER_RESET_bm (1 << 1)
#define INTERRUPT_MR0_ENABLE_bm (1 << 0)

void InitTimer0(void) {
	
	T0TCR = COUNTER_ENABLE_bm;
}

void WaitOnTimer0(unsigned int uiTime) {
	
	InitTimer0();
	
	while((uiTime*15) >= T0TC) {
		
	}
	
	T0TCR = COUNTER_RESET_bm;
	T0TC = 0;
	
}

void InitTimer0Match0(unsigned int iDelayTime) {
	
	T0MR0 = (iDelayTime*15);
	T0MCR = (COUNTER_RESET_bm | INTERRUPT_MR0_ENABLE_bm);
	
	T0TC = 0;
	InitTimer0();
}

void WaitOnTimer0Match0(unsigned int iDelayTime){
	InitTimer0Match0(iDelayTime);
	while (!(T0IR & INTERRUPT_MR0_ENABLE_bm))
  { 
		
  }
	
	T0IR |= INTERRUPT_MR0_ENABLE_bm;
}
