#include <LPC21xx.H>
#include "../Library/led.h"
#include "../Library/timer_interrupts.h"
#include "servo.h"

#define DETECTOR_bm (1 << 10)

enum ServoState {CALLIB, IDLE, IN_PROGRESS, OFFSET};

struct Servo
{
	
	enum ServoState eState; 
	unsigned int uiCurrentPosition; 
	unsigned int uiDesiredPosition;
	unsigned int uiWaitCounter;
	unsigned int uiWaitTime;
	
};

enum DetectorState {ACTIVE, INACTIVE};

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
				
		case OFFSET:
				
				if(sServo.uiCurrentPosition == 12) {

					sServo.eState = IDLE;
				} else {
					
					LedStepRight();
					sServo.uiCurrentPosition++;
				}
			break;
				
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
			
		}
}

void ServoInit(unsigned int uiServoFrequency) {
	
	float fServoTime = 0;
	
	sServo.uiWaitCounter = 0;
	
	LedInit();
	
	fServoTime = (1/(float)uiServoFrequency); // w s
	fServoTime *= 1000000; // w us
	Timer0Interrupts_Init(fServoTime, &Automat);
	
	ServoCallib();
}

void ServoCallib(void) {

	sServo.eState = CALLIB;
	while(sServo.eState == CALLIB) {

	}
}

void ServoGoTo(unsigned int uiPosition) {

	sServo.uiDesiredPosition = uiPosition;
	sServo.eState = IN_PROGRESS;
	while(sServo.eState == IN_PROGRESS) {

	}
}
