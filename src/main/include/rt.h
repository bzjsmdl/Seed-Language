#ifndef Seed_Language_rt_H
#define Seed_Language_rt_H

#include "Main.h"

void help();
unsigned long int flen(FILE* src);
void PrintError(int state);

unsigned char* state(char* text, unsigned long long int length);

#endif