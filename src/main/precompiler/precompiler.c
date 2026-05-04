#include "../include/Main.h"
extern unsigned int err;
extern CompilerTable* table;
char bufPath[260] = "./buf/tmp.seed";
char isbadbufpath= 0;
void ClearText(INTSIZE length, char* text) {
	char* a = text;
	for (INTSIZE i = 0; i < length; i++) {
		if ((text[i] == '\"' || text[i] == '\'')) {
			char* b = text + i;
			char* c = Strchr(length - i, b, text + i + 1, Positive);
			i = c - text ;
			continue;
		}
		else if (Memequ(2, "//", text + i) || Memequ(2, "/*", text + i)) {
			INTSIZE k = i;
			if (Memequ(2, "//", text + i)) {
				while (k < length && text[k] != '\n') {
					a[k] = 0;
					k++;
				}
				i = k;
			}
			else {
				while (k < length && !Memequ(2, "*/", text + k)) {
					if (text[k] != '\n') a[k] = 0;
					k++;
				}
				a[k] = 0;
				a[k + 1] = 0;
				i = k;
			}
		}
	}
}
