#include "include/Main.h"
unsigned char* state(char* text, unsigned long long int length) {
    unsigned char* Arr = malloc(length);
    for (int i = 0; i < length; i++) {
        if (isalnum(text[i])) Arr[i] = Character;
        else if (!(text[i] >= '\0' || text[i] <= ' ')) Arr[i] = Delimter;
        else if (text[i] == '\n' || text[i] == ' ') Arr[i] = Special_Delimter;
        else Arr[i] = NotCharacter;
    }
    return Arr;
}