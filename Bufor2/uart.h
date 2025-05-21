#ifndef UART_H
#define UART_H

#define RECIEVER_SIZE 12

void UART_InitWithInt(unsigned int uiBaudRate);

void Reciever_PutCharacterToBuffer(char cCharacter);

enum eRecieverStatus {EMPTY, READY, OVERFLOW};
enum eRecieverStatus eReciever_GetStatus(void);

void Reciever_GetStringCopy(char * ucDestination);

#endif
