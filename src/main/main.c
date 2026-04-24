#include "include/Main.h"
unsigned int err = NoError;
unsigned long long int Line = 0;
char* DefaultPath = "a.asm";
char defaultRT = Seed;
CompilerTable* table;
int main(int argc, const char** argv) {
	char* text = NULL;
	if (argc <= 1) {
		help();
		goto Err;
	}
	table = malloc(sizeof(CompilerTable));
	if (table == NULL) {
		err = AllocMemoryError;
		goto noErr;
	}
	for (unsigned int i = 1; i < argc; i++) {
		if (Strequ(argv[i], "-\0")) continue;
		else {
			if (Strequ(argv[i], "-h") || Strequ(argv[i], "--help")) {
				help();
				goto noErr;
			}
			else if (Strequ(argv[i], "-f") || Strequ(argv[i], "--file")) {
				if (i + 2 < argc && !(Strequ(argv[i + 1], "-\0") || Strequ(argv[i + 2], "-\0"))) {
					defaultRT = (Strequ(argv[i + 1], "ir")) ? IR : Seed;
					table->Input_File = argv[i + 2];
					i++;
				}
				else {
					err = CommandLineMissingArgument;
					goto Err;
				}
				continue;
			}
			else if (Strequ(argv[i], "-o") || Strequ(argv[i], "--output")) {
				if (i + 2 < argc && !(Strequ(argv[i + 1], "-\0") || Strequ(argv[i + 2], "-\0"))) {
					table->Target = argv[i + 1];
					table->Output_File = argv[i + 2];
					i += 2;
				}
				else {
					err = CommandLineMissingArgument;
					goto Err;
				}
				continue;
			}
		}
	}
	FILE* src = fopen(table->Input_File, "r");
	if (src == NULL) {
		err = CannotOpenFile;
		goto clear;
	}
	unsigned long long int length = flen(src);
	// printf("length : %llu\n", length);
	text = malloc(length);
	if (text == NULL) {
		err = AllocMemoryError;
		goto clear;
	}
	fread(text, length, 1, src);
	if (defaultRT == IR) {
		IRtranS(text);
	}
	Token* p = Lexer(length, text);
	// Token* head = p;
	// while (p->next != NULL) {
	// 	printf("Text: ");
	// 	print(p->texts, p->len);
	// 	printf("\nlen: %d\n", p->len);
	// 	printf("Type: %d\n", p->type);
	// 	printf("Line: %d\n\n", p->line);
	// 	p = p->next;
	// }
	clear:
		fclose(src);
		if (text != NULL) free(text);
		if (err != NoError) goto Err;
	noErr:
		printf("%u\n", err);
		return 0;
	Err:
		PrintError(table->Input_File, Line);
		return 1;
}
