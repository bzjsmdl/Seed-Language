#include "../include/Main.h"
extern unsigned int err;
void help() {
    printf(fromat);
    printf(option);
}
unsigned long long int flen(FILE* src) {
    unsigned long long int length = 0;
    fseek(src, 0, SEEK_END);
    length = ftell(src);
    fseek(src, 0, SEEK_SET);
    return length;
}

void PrintError() {
    if (err = CannotOpenFile) printf(CNOF);
    else if (err == AllocMemoryError) printf(AM);
    else if (err == UnknowLacolLabel) printf(ULL);
    else if (err == DifinedSectionNameError) printf(DSNE);
    else if (err = CommandLineMissingArgument) printf(CLAM);
    else printf("Unknow Error...");
}

void print(char* str, unsigned long long int len) {
    for (unsigned long long int i = 0; i < len; i++) printf("%c", str[i]);
}