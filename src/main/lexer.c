#include "include/Main.h"
extern unsigned int err;
Token* Lexer(unsigned long long int length, char* text) {
	unsigned char* Arr = malloc(length);
	for (unsigned long long int i = 0; i < length; i++) {
		if (isalpha(text[i])) Arr[i] = Character;
		else if (isnum(text[i])) Arr[i] = Number;
		else if (text[i] == '\"' || text[i] == '\'') Arr[i] = Quote;
		else if (text[i] == ' ') Arr[i] = Space;
		else if (ispunct(text[i])) Arr[i] = Delimter;
		else Arr[i] = NotCharacter;
	}
	Token* p = malloc(sizeof(Token)), *h = p, *n = p;
	unsigned char a[2] = {Arr[0], 0};
						//state, offset
	unsigned long long int i = 0, j = 0, line = 1;
	while (i < length) {
		if (text[i] == '\n') line++;
		if (Arr[i] != a[0] && i - 1 < length) {
			if (a[0] == Quote) {
				char* b = Strchr(length - i, text + a[1], text + i);
				p->len = b - text + 1;
				p->texts = text + a[1];
				p->type = String;
				p->line = line;
				p->next = malloc(sizeof(Token));
				n = p;
				p = p->next;
				a[1] = i;
				a[0] = Arr[i];
				j = 0;
			}
			else if (a[0] == Character) {
				p->len = j + 1;
				p->texts = text + a[1];
				p->line = line;
				p->type = isKeyword(p->texts, p->len) ? Keyword : Identifer;
				if (i <= 0 && isSdel(*(p->texts - p->len))) {
					p->texts -= 1;
					p->len += 1;
					if (*(p->texts) == '.') {
						if (Memequ(n->len, n->texts, "sec") && isSec(p->texts, p->len)) p->type = Section;
						else if (Memequ(n->len, n->texts, "pub") ||  Memequ(n->len, n->texts, "priv")) p->type = LocalLabel;
						else {
							err = Memequ(n->len, n->texts, "sec") ? DifinedSectionNameError : UnknowLacolLabel;
							return NULL;
						}
					}
					else if (*(p->texts) == '#') p->type = Preprocess_Directive;
					else if (*(p->texts) == '%') p->type = Placeholder;
					else if (*(p->texts) == '@') p->type = Attribute;
				}
				p->next = malloc(sizeof(Token));
				n = p;
				p = p->next;
				a[1] = i;
				a[0] = Arr[i];
				j = 0;
			}
		}
		else if (i - 1 < length) {
			;
		}
		i++;
		j++;
	}
}
