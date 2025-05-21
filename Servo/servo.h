#ifndef SERVO_H
#define SERVO_H

void DetectorInit(void);

void ServoInit(unsigned int uiServoFrequency);

void ServoCallib(void);

void ServoGoTo(unsigned int uiPosition);

void ServoWait(void);


#endif
