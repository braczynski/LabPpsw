#include <LPC21xx.H>
#include "led.h"
#include "timer_interrupts.h"
#include "servo.h"

#define DETECTOR_bm (1 << 10)

void DetectorInit() {
	
	IO0DIR &= ~(DETECTOR_bm);
}

enum DetectorState eReadDetector() {
	
	if ((IO0PIN & DETECTOR_bm) == 0) {
		
		return ACTIVE;
	} else {
		
		return INACTIVE;
	}
}

struct Servo sServo;

void Automat() {
	
		switch(sServo.eState) {
		
			case IDLE:
				if( sServo.uiCurrentPosition != sServo.uiDesiredPosition ) {
					
					sServo.eState = IN_PROGRESS;
				} else {
					
					sServo.eState = IDLE;
				}
			break;
				
			case IN_PROGRESS:
				
				if( sServo.uiCurrentPosition < sServo.uiDesiredPosition ) {
					
					LedStepRight();
					sServo.uiCurrentPosition++;
				} else if( sServo.uiCurrentPosition > sServo.uiDesiredPosition ) {
					
					LedStepLeft();	
					sServo.uiCurrentPosition--;
				} else if ( sServo.uiCurrentPosition == sServo.uiDesiredPosition ){
					
					sServo.eState = IDLE;
				} else {

					sServo.eState = IN_PROGRESS;
				}
			break;
			
			case CALLIB:
				
				if( eReadDetector() == ACTIVE) {
					
					sServo.uiCurrentPosition = 0;
					sServo.uiDesiredPosition = 0;
					sServo.eState = IDLE;
				} else {
					
					LedStepLeft();
					sServo.eState = CALLIB;
				}
			break;
		}
}

void ServoInit(unsigned int uiServoFrequency) {
	
	float fServoTime = 0;
	
	sServo.eState = CALLIB;
	
	LedInit();
	
	fServoTime = (1/(float)uiServoFrequency); // w s
	fServoTime *= 1000000; // w us
	Timer0Interrupts_Init(fServoTime, &Automat);
}

void ServoCallib(void) {

	sServo.eState = CALLIB;
}
/*
void ServoGoTo(unsigned int uiPosition) {

	sServo.uiDesiredPosition = uiPosition;
}
*/
void ServoGoToInDegree(unsigned int uiDegree) {

	sServo.uiDesiredPosition = (unsigned int)((float)uiDegree/(float)7.5);
}

void ServoGoTo(unsigned int uiPosition) {
	
	sServo.uiDesiredPosition = (unsigned int)((float)0.24 * (float)uiPosition);
}
