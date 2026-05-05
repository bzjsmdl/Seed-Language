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
int PStype(char* type) {
	Line = 1;
	for (INTSIZE i = 0; i < idx - 1; i++) {
		if (type[i] == Keyword) {
			if (type[i + 1] == NewLine) goto itg;
			else continue;
		}
		else if (type[i] == Identifer || type[i] == Data) {
			if (type[i + 1] == NewLine || type[i + 1] == Separator) continue;
			else goto itg;
		}
		else {
			if (type[i] == NewLine) Line++;
			continue;
		}
	}
	return 1;
	itg:
		err = InvalidTypeGroup;
	err:
		return 0;
}

int PSgrammer(char* type, char** txt) {
	Line = 1;
	for (INTSIZE i = 0; i < idx; i++) {
		if (type[i] == NewLine) Line++;
		else if (type[i] == Keyword) {
			if (Strequ(txt[i], "sec") || Strequ(txt[i], "pub") || Strequ(txt[i], "loc") || Strequ(txt[i], "priv")) {
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
					if (i + 3 >= idx) {
						err = MissingClosingBrace;
						return 0;
					}
				}
			}
			else if (Strequ(txt[i], "nop") || Strequ(txt[i], "ret")) {
				if (i + 1 >= idx || txt[i + 1][0] != ';') {
					err = SentenceMissTheEnd;
					return 0;
				}
				continue;
			}
		}
		else if (type[i] == Separator && (txt[i][0] != ';' || txt[i][0] != '{' || txt[i][0] != '}')) {
			if (txt[i][0] == '!') {
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
}
