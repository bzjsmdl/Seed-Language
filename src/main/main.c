#include "include/Main.h"
unsigned int err = NoError;
INTSIZE Line = 0;
char* DefaultPath = "a.asm";
CompilerTable* table;
extern INTSIZE idx;
extern char* txt[0x4000000 / sizeof(void*)];
extern char bufPath[260];
extern char isbadbufpath;
char* type = NULL;
const char* path;
int main(int argc, const char** argv) {
	char IsErrInt = 0;
	if (argc <= 1) {
		help();
		goto Err;
	}
	table = malloc(sizeof(CompilerTable));
	table->Path = argv[0];
	table->Output_File = DefaultPath;
	table->Target = "asm";
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
			else if (Strequ(argv[i], "-ei") || Strequ(argv[i], "--error")) {
				IsErrInt = 1;
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
	path = table->Input_File;
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
	// printf("\nidx: %lu\n", idx);
	type = calloc(idx, 1);
	if (type == NULL) {
		err = AllocMemoryError;
		goto clear;
	}
	Type(type);
	for (INTSIZE i = 0; i < idx; i++) {
		if (0 > type[i] || type[i] > 4) {
			err = UnkownToken;
			goto clear;
		}
		// if (type[i] == Keyword) printf("\nType: Keyword\n");
		// else if (type[i] == Identifer) printf("\nType: Identifer\n");
		// else if (type[i] == NewLine) printf("\nType: NewLine\n");
		// else if (type[i] == Separator) printf("\nType: Separator\n") ;
		// else if (type[i] == Data) printf("\nType: Data\n");
	}
	if (PStype(type) == 0) {
		goto clear;
	}
	if (PSgrammer(type, txt) == 0) {
		goto clear;
	}
	generate(txt);
	clear:
		fclose(src);
		if (txt[0] != 0) {
			for (INTSIZE i = 0; i < idx; i++) {
    			free(txt[i]);
			}
		}
		if (type != NULL) free(type);
		if (text != NULL) free(text);
		if (err != NoError) goto Err;
	noErr:
		return 0;
	Err:
		if (IsErrInt == 0) PrintError(path, Line);
		else printf(errorlocation "\nErr: %d\n", path, Line, err);
		return 1;
}
