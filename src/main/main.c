#include "include/Main.h"
unsigned int err = NoError;
unsigned long long int Line = 1;
char* DefaultPath = "a.asm";
CompilerTable* table;
extern INTSIZE idx;
extern char* txt[0x4000000 / sizeof(void*)];
extern char bufPath[260];
extern char isbadbufpath;

int main(int argc, const char** argv) {
	if (argc <= 1) {
		help();
		goto Err;
	}
	table = malloc(sizeof(CompilerTable));
	table->Path = argv[0];
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
				if (i + 1 < argc && !(Strequ(argv[i + 1], "-\0"))) {
					table->Input_File = argv[i + 1];
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
	FILE* src = fopen(table->Input_File, "rb");
	if (src == NULL) {
		err = CannotOpenFile;
		goto clear;
	}
	INTSIZE length = flen(src);
	char* text = malloc(length + 1);
	if (text == NULL) {
		err = AllocMemoryError;
		goto clear;
	}
	fread(text, length, 1, src);
	text[length] = 0;
	fclose(src);

	ClearText(length, text);
	if (err != NoError) goto Err;
	int a = lexer(length, text);
	if (a == 0) {
		goto clear;
	}
	clear:
		fclose(src);
		if (text != NULL) free(text);
		if (err != NoError) goto Err;
	noErr:
		return 0;
	Err:
		PrintError(table->Input_File, Line);
		return 1;
}
