#include "../include/Main.h"
extern unsigned int err;
extern unsigned long long int Line;

Token* Lexer(INTSIZE length, char* text) {
	char* s = state(length, text);
	// for (INTSIZE i = 0; i < length; i++) {
	// 	printf("(%c) : %d\n", text[i], s[i]);
	// };
	Token *t = malloc(sizeof(Token)), *head = t;
	t->back = NULL;
	char buf[8] = {0};
	buf[0] = s[0];
	INTSIZE j = 0;
	for (INTSIZE i = 0; i < length; i++) {
		if (s[i] != buf[0]){
			if (buf[0] == Quote) { // String
				
			}
		}
		j++;
	}
	return t;
}