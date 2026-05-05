#include "../include/Main.h"
// ; Double-Character-Picking Lexer
// ; Rule:
// ;    0         1    
// ;   Alpha: Is String? All Character(Not '"' or "'" and \n) : Character + Number + '_' + '.'
// ;   Delimter: Is String? All Character(Not '"' or "'" and \n) : Delimter + Character + Number
// ;   Number: Is String? All Character(Not '"' or "'" and \n) : Number + 'A','B','C','D','E','F'(and their lower) + 'x'
char* txt[0x4000000 / sizeof(void*)] = {0};
INTSIZE idx = 0;
extern unsigned int err;
extern INTSIZE Line;
int lexer(INTSIZE length, char* text) {
    char a[2] = {0}, isStr = 0, quote = 0, *b;
    INTSIZE start = 0;
    for (INTSIZE i = 0; i < length; i++) {
        a[0] = text[i];
        a[1] = text[i + 1];
        if (isStr) {
            if (a[0] == quote) goto s;
            else if (a[0] == '\n' || i + 1 < length) {
                err = MissingClosingQuote;
                return 0;
            }
            continue;
        }
        else {
            if (a[0] == '\"' || a[0] == '\'') goto s;
            else if (Isalpha(a)) {
                if (Isalpha(a + 1) || Isnum(a + 1) || a[1] == '_' || a[1] == '.') continue;
                else goto addp;
            }
            else if (Isnum(a)) {
                if (Isnum(a + 1) || a[1] == 'x' || (a[1] >= 'A' && a[1] <= 'F') || (a[1] >= 'a' && a[1] <= 'f')) continue;
                else goto addp;
            }
            else if (Ispunct(a)) {
                if (Isalpha(a + 1) || Isnum(a + 1) || Ispunct(a + 1)) continue;
                else goto addp;
            }
            else if (a[0] == '\n') {
                goto addp;
            }
            else goto clearNC;
        }
        continue;
        addp:
            b = malloc(i - start + 2);
            if (b == NULL) {
                err = AllocMemoryError;
                return 0;
            }
            txt[idx] = b;
            Strcpy(i - start + 1, text + start, b);
            b[i - start + 1] = 0;
            // printf("Text: %s\n", txt[idx]);
            idx++;
            clearNC:
                start = i + 1;
                continue;
        s:
            isStr = ~isStr;
            if (isStr == 0) goto addp;
            quote = a[0];
            continue;
    }
    return 1;
}