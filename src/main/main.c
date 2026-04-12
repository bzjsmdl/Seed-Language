#include "include/Main.h"
unsigned int err = NoError;
int main(int argc, const char** argv) {
	if (argc == 1) {
		help();
		goto Err;
	}
	CompilerTable* table = malloc(sizeof(CompilerTable));
	if (table == NULL) {
		err = AllocMemoryError;
		goto noErr;
	}
	for (int i = 1; i < argc; i++) {
		if (i == 1) table->Target = argv[i];
		else if (i == 2) table->Input_File = argv[i];
		else if (i == 3) table->Output_File = argv[i];
		if (Strequ("-h", argv[i])) help();
	}
	FILE* src = fopen(table->Input_File, "r");
	if (src == NULL) {
		err = CannotOpenFile;
		goto noErr;
	}
	unsigned long long int length = flen(src);
	printf("length : %d\n", length);
	char* text = malloc(length);
	if (text == NULL) {
		err = AllocMemoryError;
		goto noErr;
	}
	fread(text, length, 1, src);
	fclose(src);
	Token* p = Lexer(length, text);
	Token* head = p;
	while (p->next != NULL) {
		printf("Text: ");
		print(p->texts, p->len);
		printf("\nlen: %d\n", p->len);
		printf("Type: %d\n", p->type);
		printf("Line: %d\n\n", p->line);
		p = p->next;
	}
	
		
	noErr:
		free(text);
		free(head);
		return 0;
	Err: 
		PrintError();
		free(text);
		free(head);
		return 1;
}
