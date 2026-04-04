#include "../include/rt.h"
#if __SIZEOF_POINTER__ == 4
    #define ptr(pointer, offset) (pointer + offset)
#elif __SIZEOF_POINTER__ == 8
    #define ptr(pointer, offset) *(pointer + offset)
#endif
unsigned char* state(char* text, unsigned long long int length) {
    unsigned char* stateArr = malloc(length);
    for (int i = 0; i < length; i++) {
        if (Isalnum(ptr(text, i))) stateArr[i] = Character;
        else if (!Isctrl(ptr(text, i)) && text[i] != ' ') stateArr[i] = Delimter;
        else if (text[i] == '\n' || text[i] == ' ') stateArr[i] == Special_Delimter;
        else stateArr[i] = NotCharacter;
    }
    return stateArr;
}