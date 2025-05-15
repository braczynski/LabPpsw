#include "konwersje_PO.h"

#define NULL 0

void UIntToHexStr(unsigned int uiValue, char pcStr[]) {

    unsigned char ucNibbleCounter;
    unsigned char ucCurrentNibble;

    pcStr[0] = '0';
    pcStr[1] = 'x';
    pcStr[6] = NULL;
    for(ucNibbleCounter = 0 ; ucNibbleCounter < 4 ; ucNibbleCounter++) {
        ucCurrentNibble = (uiValue >> (ucNibbleCounter * 4)) & 0x0F;
        if(ucCurrentNibble<10)
        {
            pcStr[5 - ucNibbleCounter] = '0' + ucCurrentNibble;
        }
        else
        {
            pcStr[5 - ucNibbleCounter] = 'A' + (ucCurrentNibble - 10);
        }
    }
}

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue) {

    unsigned char ucCurrentCharacter;
    unsigned char ucCharacterCounter;

    *puiValue = 0;

    if ((pcStr[0] != '0') || (pcStr[1] != 'x') || (pcStr[2] == NULL)) {
        return ERROR;
    }

    for (ucCharacterCounter = 2; pcStr[ucCharacterCounter] !=NULL; ucCharacterCounter++) {
        ucCurrentCharacter = pcStr[ucCharacterCounter];
        if (ucCharacterCounter == 6)
        {
            return ERROR;
        }
        *puiValue = *puiValue << 4;
        if((ucCurrentCharacter <= '9') && (ucCurrentCharacter >= '0'))
        {
            *puiValue = (*puiValue) | (ucCurrentCharacter - '0');
        }
        else if((ucCurrentCharacter <= 'F') && (ucCurrentCharacter >= 'A'))
        {
            *puiValue = (*puiValue) | (ucCurrentCharacter - 'A' + 10);
        }
        else
        {
            return ERROR;
        }
    }
    return OK;
}

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]) {

    unsigned char ucArrayEndCounter;

    for(ucArrayEndCounter=0; pcDestinationStr[ucArrayEndCounter] != NULL; ucArrayEndCounter++) {

    }

    UIntToHexStr(uiValue, (pcDestinationStr + ucArrayEndCounter));
}
