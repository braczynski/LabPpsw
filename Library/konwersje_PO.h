#ifndef KONWERSJE_PO_H
#define KONWERSJE_PO_H

enum Result {
    OK = 0,
    ERROR = 1
};

void UIntToHexStr(unsigned int uiValue, char pcStr[]);

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue);

void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]);

#endif
