#include "../include/Main.h"
extern INTSIZE Line;
extern INTSIZE idx;
extern CompilerTable* table;
extern unsigned int err;
extern const char* path;
extern char* type;
int generate(char** txt) {
	FILE* output = fopen(table->Output_File, "wb");  
	if (output == NULL) {
		err = CannotOpenFile;
		return 0;
	}
	path = table->Output_File;
	INTSIZE state = 0, j = 0;
	for (INTSIZE i = 0; i < idx; i++) {
		if (Strequ(txt[i], "sec")) {
			fprintf(output, "section %s\n", txt[i + 1]);
			i++;
		}
		else if (Strequ(txt[i], "extern")) {
			INTSIZE k = i + 1;
			fprintf(output, "extern ");
			for (;k < idx && !Strequ(";", txt[k]); k++){
				fprintf(output, "%s", txt[k]);
			}
			fprintf(output, "\n");
			i = k;
		}
		else if (Strequ(txt[i], "pub")) {
			fprintf(output, "global %s\n%s:\n", txt[i + 1], txt[i + 1]);
			i++;
		}
		else if (Strequ(txt[i], "loc")) {
			fprintf(output, ".%s:\n", txt[i + 1]);
			i++;
		}
		else if (Strequ(txt[i], "priv")) {
			fprintf(output, "%s:\n", txt[i + 1]);
			i++;
		}
		else if (Strequ(txt[i], "nop") || Strequ(txt[i], "rep") || Strequ(txt[i] ,"repe") ||Strequ(txt[i] ,"repne")){ 
			if (txt[i + 1] == NULL || type[i + 1] == NewLine) {
				fprintf(output, "%s\n", txt[i]);
			}
			else fprintf(output, "%s ", txt[i]);
		}
		else if (Strequ(txt[i], "=>")) {
			if (Strequ("df", txt[i + 1]) || Strequ("if", txt[i + 1]) || Strequ("cf", txt[i + 1]) \
			  || Strequ("DF", txt[i + 1]) || Strequ("IF", txt[i + 1]) || Strequ("CF", txt[i + 1])) {
				if (Strequ("df", txt[i + 1]) || Strequ("DF", txt[i + 1])) {
					if (Strequ("1", txt[i - 1])) fprintf(output, "std\n");
					else if (Strequ("0", txt[i - 1])) fprintf(output, "cld\n");
				}
				else if (Strequ("if", txt[i + 1]) || Strequ("IF", txt[i + 1])) {
					if (Strequ("1", txt[i - 1])) fprintf(output, "sti\n");
					else if (Strequ("0", txt[i - 1])) fprintf(output, "cli\n");
				}
				else if (Strequ("cf", txt[i + 1]) || Strequ("CF", txt[i + 1])) {
					if (Strequ("1", txt[i - 1])) fprintf(output, "stc\n");
					else if (Strequ("0", txt[i - 1])) fprintf(output, "clc\n");
				}
				i ++;
			}
			else {
				j = i;
				for (; type[j] != NewLine && !(Strequ(txt[j], "*") || Strequ(txt[j], ";")); j--);
				// printf("txt[j - 1]: %s\ntxt[j]: %s\n", txt[j - 1], txt[j]);
				if (isType(txt[j - 1])) {
					fprintf(output, "mov %s [", txt[j - 1]);
					INTSIZE k = j + 1;
					// printf("txt[k]: %s\n", txt[k]);
					for (;k < idx && !Strequ(txt[k], "=>"); k++) {
						// printf("txt[k]: %s\n", txt[k]);
						fprintf(output, "%s", txt[k]);
					}
					fprintf(output, "], %s\n", txt[i + 1]);
					i = k;
				}
				else if (isType(txt[i + 1])) {
					fprintf(output, "mov %s [", txt[i + 1]);
					INTSIZE k = i + 3;
					for (; !Strequ(txt[k], ";"); k++) {
						// printf("txt[k]: %s\n", txt[k]);
						fprintf(output, "%s", txt[k]);
					}
					// printf("txt[i - 1]: %s\n", txt[i - 1]);
					fprintf(output, "], %s\n", txt[i - 1]);
					i = k;
				}
				else {
					fprintf(output, "mov %s, %s\n", txt[i + 1], txt[i - 1]);
					i++;
				}
			}
		}
		else if (Strequ(txt[i], "cmp")) {
			fprintf(output, "%s ", txt[i]);
			if (isType(txt[i + 1])) {
				fprintf(output, "%s [", txt[i + 1]);
				INTSIZE k = i + 3;
				// printf("txt[k]: %s\n", txt[k]);
				for (;k < idx && !Strequ(txt[k], ","); k++) {
					// printf("txt[k]: %s\n", txt[k]);
					fprintf(output, "%s", txt[k]);
				}
				j = i;
				for (; type[j] != NewLine && !(Strequ(txt[j], ";")); j++);
				fprintf(output, "], %s\n", txt[j - 1]);
				i = k;
			}
			else {
				j = i;
				for (; type[j] != NewLine && !(Strequ(txt[j], "*") || Strequ(txt[j], ";")); j++);
				if (isType(txt[j - 1])) {
					fprintf(output, "%s, %s [", txt[i + 1], txt[j - 1]);
					INTSIZE k = j + 1;
					for (; !Strequ(txt[k], ";"); k++) {
						// printf("txt[k]: %s\n", txt[k]);
						fprintf(output, "%s", txt[k]);
					}
					// printf("txt[i - 1]: %s\n", txt[i - 1]);
					fprintf(output, "]\n");
					i = k;
				}
				else fprintf(output, "%s %s\n", txt[i + 1], txt[i + 3]);
			}
			i += 2;
		}
		else if (Strequ(txt[i], "ret")) {
			if (Strequ(txt[i + 1], "~")) {
				fprintf(output, "%s\n", txt[i]);
			}
			else {
				fprintf(output, "%s %s\n", txt[i], txt[i + 1]);
			}
			i += 2;
		}
		else if (Strequ(txt[i], "jmp") || Strequ(txt[i], "je") || Strequ(txt[i], "jne") || Strequ(txt[i], "loop") || Strequ(txt[i] ,"loopne") ||Strequ(txt[i] ,"loope")) {
			if (isType(txt[i + 1])) {
				fprintf(output, "%s %s [", txt[i], txt[i + 1]);
				INTSIZE k = i + 3;
				for (; !Strequ(txt[k], ";"); k++) {
					fprintf(output, "%s", txt[k]);
				}
				fprintf(output, "]", txt[k]);
				i += k;
			}
			else {
				fprintf(output, "%s %s\n", txt[i], txt[i + 1]);
				i++;
			}
		}
		else if (Strequ(txt[i], "pop") || Strequ(txt[i], "push") || Strequ(txt[i], "call") || Strequ(txt[i], "inc") || Strequ(txt[i], "dec")) {
			if (isType(txt[i + 1])) {
				INTSIZE k = i + 2;
				if ((Strequ(txt[k + 1], "flags") || Strequ(txt[k + 1], "eflags") || Strequ(txt[k + 1], "rflags")) && (Strequ(txt[i], "pop") || Strequ(txt[i], "push"))) {
					if (Strequ(txt[k + 1], "flags")) fprintf(output, "%sf\n");
					else if (Strequ(txt[k + 1], "eflags")) fprintf(output, "%sfd\n");
					else if (Strequ(txt[k + 1], "rflags")) fprintf(output, "%sfq\n");
					i += k;
				}
				else {
					fprintf(output, "%s %s [", txt[i], txt[i + 1]);
					for (; !Strequ(txt[k], ";"); k++) {
						fprintf(output, "%s", txt[k]);
					}
					fprintf(output, "]", txt[k]);
					i += k;
				}
			}
			else {
				fprintf(output, "%s %s\n", txt[i], txt[i + 1]);
				i++;
			}
		}
		else if (isType(txt[i])) {
			if (Strequ(txt[i - 1], "res")) {
				if (Strequ(txt[i], "byte")) fprintf(output, "resb %s\n", txt[i + 1]);
				else if (Strequ(txt[i], "qword")) fprintf(output, "resq %s\n", txt[i + 1]);
				else if (Strequ(txt[i], "dword")) fprintf(output, "resd %s\n", txt[i + 1]);
				else if (Strequ(txt[i], "word")) fprintf(output, "resw %s\n", txt[i + 1]);
				i += 2;
			}
			else if (Strequ(txt[i - 1], "cpy")) {
				if (Strequ(txt[i], "byte")) fprintf(output, "movsb\n");
				else if (Strequ(txt[i], "qword")) fprintf(output, "movsq\n");
				else if (Strequ(txt[i], "dword")) fprintf(output, "movsd\n");
				else if (Strequ(txt[i], "word")) fprintf(output, "movsw\n");
				i += 2;
			}
			else if (Strequ(txt[i - 1], "write")) {
				if (Strequ(txt[i], "byte")) fprintf(output, "stosb\n");
				else if (Strequ(txt[i], "qword")) fprintf(output, "stosq\n");
				else if (Strequ(txt[i], "dword")) fprintf(output, "stosd\n");
				else if (Strequ(txt[i], "word")) fprintf(output, "stosw\n");
				i += 2;
			}
			else if (Strequ(txt[i - 1], "read")) {
				if (Strequ(txt[i], "byte")) fprintf(output, "lodsb\n");
				else if (Strequ(txt[i], "qword")) fprintf(output, "lodsq\n");
				else if (Strequ(txt[i], "dword")) fprintf(output, "lodsd\n");
				else if (Strequ(txt[i], "word")) fprintf(output, "lodsw\n");
				i += 2;
			}
			else if (Strequ(txt[i - 1], "find")) {
				if (Strequ(txt[i], "byte")) fprintf(output, "scasb\n");
				else if (Strequ(txt[i], "qword")) fprintf(output, "scasq\n");
				else if (Strequ(txt[i], "dword")) fprintf(output, "scasd\n");
				else if (Strequ(txt[i], "word")) fprintf(output, "scasw\n");
				i += 2;
			}
			else if (Strequ(txt[i - 1], "putpd")) {
				if (Strequ(txt[i], "byte")) fprintf(output, "outsb\n");
				else if (Strequ(txt[i], "dword")) fprintf(output, "outsd\n");
				else if (Strequ(txt[i], "word")) fprintf(output, "outsw\n");
				i += 2;
			}
			else if (Strequ(txt[i - 1], "getpd")) {
				if (Strequ(txt[i], "byte")) fprintf(output, "insb\n");
				else if (Strequ(txt[i], "dword")) fprintf(output, "insd\n");
				else if (Strequ(txt[i], "word")) fprintf(output, "insw\n");
				i += 2;
			}
			else if (txt[i + 1][0] != '*'){
				if (Strequ(txt[i], "byte")) {
					fprintf(output, "db ");
				}
				else if (Strequ(txt[i], "qword")) {
					fprintf(output, "dq ");
				}
				else if (Strequ(txt[i], "dword")) {
					fprintf(output, "dd ");
				}
				else if (Strequ(txt[i], "word")) {
					fprintf(output, "dw ");
				}
				INTSIZE k = i + 1;
				for (; k < idx && !Strequ(";", txt[k]); k++) {
					// printf("txt[k]: %s\n", txt[k]);
					fprintf(output, "%s", txt[k]);
				}
				fprintf(output, "\n");
				i = k;
			}
		}
		else if (isACO(txt[i])) {
			j = i;
			for (; type[j] != NewLine && !(Strequ(txt[j], "*") || Strequ(txt[j], ";")); j--);
			if (txt[j][0] == '*') continue;
			else {
				if (Strequ("^", txt[i])) {
					fprintf(output, "xor %s, %s\n", txt[i - 1], txt[i + 1]);
				}
				else if (Strequ("+", txt[i])) {
					fprintf(output, "add %s, %s\n", txt[i - 1], txt[i + 1]);
				}
				else if (Strequ("-", txt[i])) {
					fprintf(output, "sub %s, %s\n", txt[i - 1], txt[i + 1]);
				}
				else if (Strequ("<<", txt[i])) {
					fprintf(output, "shl %s, %s\n", txt[i - 1], txt[i + 1]);
				}
				else if (Strequ(">>", txt[i])) {
					fprintf(output, "shr %s, %s\n", txt[i - 1], txt[i + 1]);
				}
				else;
			}
		}
		else if (type[i] == NewLine) j = i;
		// printf("%lu/%lu\n", i, idx);
		else continue;
	}
	fclose(output);
	return 1;
}