#include <LPC21xx.H>

#define NULL 0


void CopyString(char pcSource[], char pcDestination[]) {

    unsigned char ucCharacterCounter;

    for (ucCharacterCounter = 0; pcSource[ucCharacterCounter] != NULL; ucCharacterCounter++) {
        pcDestination[ucCharacterCounter] = pcSource[ucCharacterCounter];
    }

    pcDestination[ucCharacterCounter] = NULL;
}

int main(void) {
    //TEST COPYSTRING
    char cSource[6] = "grzyb";
    char cDestination[8] = "ek";

    CopyString(cSource, cDestination);
    return 0;
}