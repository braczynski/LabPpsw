#include "string.h"
#include "command_decoder.h"

#define NULL 0

struct Keyword asKeywordList[MAX_KEYWORD_NR] =
{
		{GT, "goto"},
		{CAL, "callib"}
};

Token asToken[MAX_TOKEN_NR];
unsigned char ucTokenNr = 0;

enum FindTokenState {TOKEN, DELIMITER};

unsigned char ucFindTokensInString (char *pcString) {

    enum FindTokenState eFindTokenState = DELIMITER;
    unsigned char ucTokenCounter = 0;
    char cCurrentCharacter = pcString[0];
    unsigned char ucArrayIndex;

    for (ucArrayIndex = 0;;ucArrayIndex++) {

        cCurrentCharacter = pcString[ucArrayIndex];

        switch (eFindTokenState) {
        case TOKEN: {

					if (cCurrentCharacter == DELIMITER_CHARACTER) {

							eFindTokenState = DELIMITER;
          } else if(ucTokenCounter == MAX_TOKEN_NR){

							return ucTokenCounter;
          } else if (cCurrentCharacter == NULL) {

							return ucTokenCounter;
          } else {

							eFindTokenState = TOKEN;
          }
        }
        break;

        case DELIMITER:

            if (cCurrentCharacter == NULL) {

							return ucTokenCounter;
              } else if (cCurrentCharacter != DELIMITER_CHARACTER) {

									asToken[ucTokenCounter].uValue.pcString = (pcString+(ucArrayIndex));
                  ucTokenCounter++;
                  eFindTokenState = TOKEN;
              } else {

                  eFindTokenState = DELIMITER;
              }
        break;
        }
    }
}

enum Result eStringToKeyword (char pcStr[],enum KeywordCode *peKeywordCode) {

    unsigned char ucKeywordCounter;

    for (ucKeywordCounter = 0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++) {
        if (eCompareString(pcStr,asKeywordList[ucKeywordCounter].cString) == EQUAL) {

            *peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
            return OK;
        }
    }
    return ERROR;
}

void DecodeTokens(void) {

    unsigned char ucTokenCounter;
    enum  Result eKeywordCheck = ERROR;
    enum Result eResult = OK;
    Token *pcToken = asToken;

    for (ucTokenCounter = 0; (ucTokenCounter < ucTokenNr); ucTokenCounter++) {

        eKeywordCheck = eStringToKeyword(pcToken->uValue.pcString, &pcToken->uValue.eKeyword);
        if (eKeywordCheck == OK) {

            pcToken->eType = KEYWORD;
        } else {

           eResult = eHexStringToUInt(pcToken->uValue.pcString,  &pcToken->uValue.uiNumber);
            if (eResult == OK) {

                pcToken->eType = NUMBER;
            } else {

                pcToken->eType = STRING;
            }
        }
        pcToken++;
    }

}

void DecodeMsg(char *pcString) {

    ucTokenNr= ucFindTokensInString(pcString);
    ReplaceCharactersInString(pcString, DELIMITER_CHARACTER, NULL);
    DecodeTokens();
}
