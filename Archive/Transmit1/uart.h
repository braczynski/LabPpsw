#ifndef UART_H
#define UART_H

#define RECIEVER_SIZE 12
#define TRANSMITER_SIZE 12

void UART_InitWithInt(unsigned int uiBaudRate);

void Reciever_PutCharacterToBuffer(char cCharacter);

enum eRecieverStatus {EMPTY, READY, OVERFLOW};
enum eRecieverStatus eReciever_GetStatus(void);

void Reciever_GetStringCopy(char * ucDestination);

enum eTransmiterStatus {FREE, BUSY};

char Transmiter_GetCharacterFromBuffer(void);

void Transmiter_SendString(unsigned char cString[]);

enum eTransmiterStatus Transmiter_GetStatus(void);


#endif
