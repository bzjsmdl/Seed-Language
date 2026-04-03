#include "../include/rt.h"
unsigned char* state(char* text, unsigned long long int length) {
    unsigned char* stateArr = malloc(length);
    for (int i = 0; i < length; i++) {
        if (Isalnum(text + i) == 1) stateArr[i] = Character;
        else if (Ispunct(text + i) == 1) stateArr[i] = Delimter;
        else if (text[i] == '\n' || text[i] == ' ') stateArr[i] == Special_Delimter;
        else stateArr[i] = NotCharacter;
    }
    return stateArr;
}