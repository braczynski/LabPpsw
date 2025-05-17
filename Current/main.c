#include <LPC21xx.H>


#include "../library/uart.h"
#include "../Library/keyboard.h"
#include "../Library/timer_interrupts.h"
#include "../library/servo.h"
#include "../library/string.h"
#include "../library/command_decoder.h"
#include "../library/timer.h"

#define NULL 0

struct Watch { 
unsigned char ucMinutes, ucSecconds; 
unsigned char fSeccondsValueChanged, fMinutesValueChanged; 
} sWatch;

void WatchUpdate() {
	
	sWatch.fSeccondsValueChanged = 1;
	if(sWatch.ucSecconds == 60) {
		
		sWatch.ucSecconds = 0;
		sWatch.fMinutesValueChanged = 1;
	}
	
}

int main(){
	
	unsigned int iMainLoopCtr;
	unsigned char ucSecString[TRANSMITER_SIZE] = "sec ";
	unsigned char ucMinString[TRANSMITER_SIZE] = "min ";
	unsigned char fCalcActived = 0;
	unsigned int uiCalcValue;
	char cCalc[RECIEVER_SIZE];
	
	KeyboardInit();
	DetectorInit();
	UART_InitWithInt(9600);
	Timer0Interrupts_Init(1000000, &WatchUpdate);
	
	while(1) {
		
		if(eReciever_GetStatus() == READY) {
			
			Reciever_GetStringCopy(cCalc);
			
			DecodeMsg(cCalc);
			
			if((0 != ucTokenNr) || (asToken[0].eType == KEYWORD)) {
				
				if(asToken[0].uValue.eKeyword == CALC) {

					fCalcActived = 1; 
				}
			}
		}
		
		if(Transmiter_GetStatus() == FREE) {
			
			if(fCalcActived == 1) {
				
				cCalc[4] = ' ';
				cCalc[5] = NULL;
				
				uiCalcValue = asToken[1].uValue.uiNumber;
				uiCalcValue = uiCalcValue * 2;
				
				AppendUIntToString(uiCalcValue, cCalc);
				Transmiter_SendString((unsigned char *)cCalc);
				
				fCalcActived = 0;
				
			} else if(sWatch.fMinutesValueChanged == 1) {

				sWatch.ucMinutes++;
				sWatch.fMinutesValueChanged=0;
				sWatch.fSeccondsValueChanged=0;
				
				AppendUIntToString(sWatch.ucSecconds, (char *)ucSecString);
				AppendUIntToString(sWatch.ucMinutes, (char *)ucMinString);
				AppendString((char *)ucMinString, (char *)ucSecString);
				
				Transmiter_SendString(ucSecString);
			} else if(sWatch.fSeccondsValueChanged == 1) {
	
				sWatch.ucSecconds++;
				sWatch.fSeccondsValueChanged=0;
				AppendUIntToString(sWatch.ucSecconds, (char *)ucSecString);
				if(sWatch.fMinutesValueChanged == 0) {
					Transmiter_SendString(ucSecString);
				}
				
			}
			
		} 
		
		ucSecString[4] = NULL;
		ucMinString[4] = NULL;
		iMainLoopCtr++;
	}
}
