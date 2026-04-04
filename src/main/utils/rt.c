#include "../include/rt.h"
void help() {
    printf(fromat);
    printf(option);
}
unsigned long int flen(FILE* src) {
    unsigned long int length = 0;
    fseek(src, 0, SEEK_END);
    length = ftell(src);
    fseek(src, 0, SEEK_SET);
    return length;
}

void PrintError(int state) {
    if (CannotReadFile) printf("CannotReadFile");
}