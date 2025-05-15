#ifndef STRING_H
#define STRING_H

enum Result {
    OK = 0,
    ERROR = 1
};

void UIntToHexStr(unsigned int uiValue, char pcStr[]);

enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue);

void AppendUIntToString(unsigned int uiValue, char pcDestinationStr[]);

void CopyString(char pcSource[], char pcDestination[]);

enum CompResult {DIFFERENT, EQUAL};
enum CompResult eCompareString(char pcStr1[], char pcStr2[]);

void AppendString (char pcSourceStr[], char pcDestinationStr[]);

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar);

#endif
