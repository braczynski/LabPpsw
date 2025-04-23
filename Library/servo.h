#ifndef SERVO_H
#define SERVO_H

void DetectorInit(void);

enum DetectorState {ACTIVE, INACTIVE};

enum DetectorState eReadDetector(void);

enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo
{
	
	enum ServoState eState; 
	unsigned int uiCurrentPosition; 
	unsigned int uiDesiredPosition;
	
};

extern struct Servo sServo;

void ServoInit(unsigned int uiServoFrequency);

void ServoCallib(void);

void ServoGoTo(unsigned int uiPosition);


#endif
