// ; PStype:
// ; Keyword + {Identifer, Data, Separator, Keyword}
// ; eg: sec .text/ byte 10/ nop;/ rep byte cpy
// ; Identifer + {Separator, NewLine}
// ; eg: byte [a]/ a => rax;/ a: byte 1;
// ; Data + {Separtor, NewLine}
// ; eg: byte 1;/ byte [1] / (1, 2, 3); / #ifequ %%os 1
// ; Separator + ALL_TYPE
// ; NewLine + ALL_TYPE
// PSgarmmer:
// define section: sec id {body}
#include "../include/Main.h"
extern INTSIZE Line;
extern INTSIZE idx;
extern unsigned int err;
extern char** txt;
int PStype(char* type) {
	Line = 1;
	INTSIZE i = 0, v2 = 0;
	for (; i < idx - 1; i++) {
		if (type[i] == Keyword) {
			if (type[i + 1] == NewLine) goto itg;
			else continue;
		}
		else if (type[i] == Identifer || type[i] == Data) {
			if (type[i + 1] == Separator) continue;
			else if (type[i + 1] == NewLine) continue;
			else goto itg;
		}
		else {
			if (type[i] == NewLine) {
				Line++;
				v2 = idx;
			}
			continue;
		}
	itg:
		// if (type[i] == Keyword) printf("\nType: Keyword\n");
		// else if (type[i] == Identifer) printf("\nType: Identifer\n");
		// else if (type[i] == NewLine) printf("\nType: NewLine\n");
		// else if (type[i] == Separator) printf("\nType: Separator\n") ;
		// else if (type[i] == Data) printf("\nType: Data\n");

		// if (type[i + 1] == Keyword) printf("\nType: Keyword\n");
		// else if (type[i + 1] == Identifer) printf("\nType: Identifer\n");
		// else if (type[i + 1] == NewLine) printf("\nType: NewLine\n");
		// else if (type[i + 1] == Separator) printf("\nType: Separator\n") ;
		// else if (type[i + 1] == Data) printf("\nType: Data\n");
		err = InvalidTypeGroup;
	err:
		return 0;
	}
	return 1;
}

int PSgrammer(char* type, char** txt) {
	INTSIZE state = 0;
	Line = 1;
	for (INTSIZE i = 0; i < idx; i++) {
		if (type[i] == NewLine) Line++;
		else if (type[i] == Keyword) {
			if (Strequ(txt[i], "sec") || Strequ(txt[i], "pub") || Strequ(txt[i], "loc") || Strequ(txt[i], "priv")) {
				if (!i == 0) {
					if (Strequ(txt[i - 1], "jmp") || Strequ(txt[i - 1], "je") || Strequ(txt[i - 1], "jne") || Strequ(txt[i - 1], "loop")) continue;
				}
				if (i + 1 >= idx) {
					err = KeywordMissingAruments;
					return 0;
				}
				else if (type[i + 1] != Identifer) {
					err = DefinedSectionOrLabelError;
					return 0;
				}
				else if (i + 2 >= idx) {
					err = KeywordMissingAruments;
					return 0;
				}
				else if (txt[i + 2][0] == '{')	 {
					if (i + 3 >= idx) goto mcbe;
				}
			}
		}
			
		else if (Strequ(txt[i], "nop")) {
			if (i + 1 >= idx || txt[i + 1][0] != ';') goto smte;
		}
		else if (Strequ(txt[i], "ret")) {
			if (i + 2 >= idx || txt[i + 2][0] != ';') goto smte;
		}
		else if (Strequ(txt[i], "cmp")) {
			if (i + 4 >= idx || txt[i + 4][0] != ';') goto smte;
		}
		else if (Strequ(txt[i], "jmp") || Strequ(txt[i], "je") || Strequ(txt[i], "jne") || Strequ(txt[i], "loop") || Strequ(txt[i], "loop")) {
			if (i + 6 >= idx) {
				goto smte;
			}
			else {
				if (i + 2 >= idx || txt[i + 2][0] != ';') goto smte;
			}
		}
		else if (type[i] == Separator && !(Strequ(txt[i], ";") || Strequ(txt[i], "{") || Strequ(txt[i], "}"))) {
			if (Strequ(txt[i], "!")) {
				if (i + 1 >= idx && (type[i + 1] != Data || type[i + 1] != Keyword)) {
					err = InvalidArithmetic;
					return 0;
				}
				continue;
			}
			else {
				if (i + 1 >= idx || i == 0) {
					err = ((i + 1 >= idx && i == 0) && isACO(txt[i])) ? InvalidArithmetic : InvalidOperation;
					return 0;
				}
			}
		}
		else continue;
	}
	return 1;
	smte:
		err = SentenceMissTheEnd;
		return 0;
	mcbe:
		err = MissingClosingBrace;
		return 0;
}
