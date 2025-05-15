#ifndef DEKODOWANIE_PO_H
#define DEKODOWANIE_PO_H

#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3
#define DELIMITER_CHARACTER ' '

typedef enum TokenType {KEYWORD, NUMBER, STRING} TokenType;

typedef enum KeywordCode { LD, ST, RST} KeywordCode;

typedef union TokenValue
{
    enum KeywordCode eKeyword; // jezeli KEYWORD
    unsigned int uiNumber; // jezeli NUMBER
    char * pcString; // jezeli STRING
} TokenValue;

typedef struct Token
{
    enum TokenType eType; // KEYWORD, NUMBER, STRING
    union TokenValue uValue; // enum, unsigned int, char*
} Token;

typedef struct Keyword
{
    enum KeywordCode eCode;
    char cString[MAX_KEYWORD_STRING_LTH + 1];
} Keyword;

extern Token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr;

unsigned char ucFindTokensInString (char *pcString);

enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode); 

void DecodeTokens(void);

void DecodeMsg(char *pcString);

#endif
