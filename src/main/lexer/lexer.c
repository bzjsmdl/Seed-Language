#include "../include/Main.h"
extern unsigned int err;
extern unsigned long long int Line;

Token* Lexer(INTSIZE length, char* text) {
	char* s = state(length, text);
	// for (INTSIZE i = 0; i < length; i++) {
	// 	printf("(%c) : %d\n", text[i], s[i]);
	// };
	Token *t = malloc(sizeof(Token)), *head = t, *now = t;
	t->back = NULL;
	char buf[8] = {0};
	buf[0] = s[0];
	INTSIZE j = 0;
	for (INTSIZE i = 0; i < length;) {
		if (s[i] == NotCharacter) {
			if (text[i] == '\n') Line++;
			continue;
		}
		if (s[i] != buf[0]){
			t->line = Line;
			if (buf[0] == Quote) { // String
				buf[1] = text[i - 1];
				INTSIZE k = i;
				j--;
				while (k < length && text[k] != buf[1]) {
					j++;
					k++;
				}
				t->len = j;
				t->texts = text + k - j;
				t->ftype = Data;
				t->ctype = String;
				t->next = malloc(sizeof(Token));
				now = t;
				t = t->next;
				t->back = now;
				i = ++k;
				buf[0] = s[i];
				j ^= j;
				continue;
			}
			else if (buf[0]) { // Placeholder
				buf[0] = s[i];
				j ^= j;
			}
		}
		j++;
		next:
			i++;
	}
	return t;
}