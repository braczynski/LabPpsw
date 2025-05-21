#include <LPC21xx.H>
#include "adc.h"

#define ADCINPUT0_bm (1<<22)
#define SELECTINPUT0_bm (1<<0)
#define STARTCONVERTNOW_bm (1<<24)
#define ADCON_bm (1<<21)

#define CONVERTDONE_bm (1<<31)
#define CONVERTDATA_BM 0xFFC0

#define RESADC 1023

// VIC (Vector Interrupt Controller) VICIntEnable
#define VIC_ADC_CHANNEL_NR 18

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE 0x00000020

unsigned int uiADCData;

//(Interrupt Service Routine) of Timer 0 interrupt
__irq void ADCIRQHandler(){
	
	uiADCData = ADDR;
	uiADCData &= CONVERTDATA_BM;
	uiADCData = (uiADCData>>6);
	
	ADCR &= (~STARTCONVERTNOW_bm);
	VICVectAddr = 0; // Acknowledge Interrupt
}

void ADC_Init(){
	
	PINSEL1 = ADCINPUT0_bm;
	ADCR = SELECTINPUT0_bm | ADCON_bm;
        // interrupts
	VICIntEnable |= (0x1 << VIC_ADC_CHANNEL_NR);            // Enable Timer 0 interrupt channel 
	VICVectCntl3  = mIRQ_SLOT_ENABLE | VIC_ADC_CHANNEL_NR;  // Enable Slot 0 and assign it to Timer 0 interrupt channel
	VICVectAddr3  =(unsigned long)ADCIRQHandler; 	   // Set to Slot 0 Address of Interrupt Service Routine 

}

void ADC_Start(){
	
	ADCR |= STARTCONVERTNOW_bm;
}

unsigned int ADCServoValue() {
	unsigned int uiPosition;
	
	uiPosition = (unsigned int)(((float)48/(float)1023) * (float)uiADCData);
	
	return uiPosition;
}
