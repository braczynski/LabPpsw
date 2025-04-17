#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE (1<<0)
#define COUNTER_RESET (1<<1)
#define RESET_ON_MR0 (1<<1)
#define INTERRUPT_ON_MR0 (1<<0)
#define INTERRUPT_FLAG_MR0 (1<<0)

void InitTimer0(void) {
	
	T0TCR = COUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiTime) {
	
	T0TCR |= COUNTER_RESET;
	T0TC = 0;
	InitTimer0();
	
	while((uiTime*15) >= T0TC) {
		
	}
	
}

void InitTimer0Match0(unsigned int uiDelayTime) {
	
	T0MR0 = (uiDelayTime*15);
	
	T0MCR |= (RESET_ON_MR0|INTERRUPT_ON_MR0);
	
	T0TCR |= COUNTER_RESET;
	T0TC = 0;
	InitTimer0();
}

void WaitOnTimer0Match0(){
	while ((T0IR & INTERRUPT_FLAG_MR0) == 0) { 
		
  }
	
	T0IR |= INTERRUPT_FLAG_MR0;
}
