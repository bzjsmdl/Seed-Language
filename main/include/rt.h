#ifndef Seed_Language_rt_H
#define Seed_Language_rt_H

#include "Main.h"

void help();
unsigned long int flen(FILE* src);
void PrintError(int state);

#if __SIZEOF_POINTER__ == 4
    unsigned char* state(char* text, unsigned int length);
#elif __SIZEOF_POINTER__ == 8
    unsigned char* state(char* text, unsigned long long int length);
#endif

#endif