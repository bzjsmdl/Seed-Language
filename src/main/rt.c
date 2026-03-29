#include "include/rt.h"
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
int Strlen64(const char* string) {
    unsigned long long int i = 0;
    for (; string[i] != '\0'; i++);
    return (i);
}
int Strequ64(const char* str1, const char* str2) {
    if (Strlen64(str1) != Strlen64(str2)) return 0;
    for (unsigned long long int i = 0; i < Strlen64(str1); i++) 
        if (str1[i] != str2[i]) return 0;
    return 1;
}