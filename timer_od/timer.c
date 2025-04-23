#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE (1<<0)
#define COUNTER_RESET (1<<1)
#define RESET_ON_MR0 (1<<1)
#define INTERRUPT_ON_MR0 (1<<0)
#define INTERRUPT_FLAG_MR0 (1<<0)

void InitTimer0(void) {
	
	T0TCR = COUNTER_ENABLE; // uruchamia timer
}

void WaitOnTimer0(unsigned int uiTime) {
	
	T0TCR |= COUNTER_RESET; // resetuje timer
	T0TC &= (~COUNTER_RESET); // zerowanie flagi resetu
	
	while((uiTime*15) >= T0TC) { //czekam az rejestr TC osiagnie zadana wartosc
		
	}
	
}

void InitTimer0Match0(unsigned int uiDelayTime) {
	
	T0MR0 = (uiDelayTime*15); // Wpisujemy do T0MR0 zadana wartosc taktow (ile ma czekac)
	
	T0MCR |= (RESET_ON_MR0|INTERRUPT_ON_MR0); // ustawiam timer by zglosil przerwanie gdy rejestr TC=T0MR0 i ustawiam timer by zresetowal rejestr TC gdy rejestr TC=T0MR0  
	
	T0TCR |= COUNTER_RESET; // resetuje timer
	T0TC &= (~COUNTER_RESET); // zerowanie flagi resetu
	InitTimer0(); // uruchamia timer
}

void WaitOnTimer0Match0(){ 
	while ((T0IR & INTERRUPT_FLAG_MR0) == 0) { // czekam na ustaweinei flagi przerwania
		
  }
	
	T0IR = INTERRUPT_FLAG_MR0; //usuwa nam flage przerwania
}
