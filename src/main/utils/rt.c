#include "../include/Main.h"
extern unsigned int err;
void help() {
	printf("%s", chelp);
}
unsigned long long int flen(FILE* src) {
	unsigned long long int length = 0;
	fseek(src, 0, SEEK_END);
	length = ftell(src);
	fseek(src, 0, SEEK_SET);
	return length;
}

void PrintError(const char* path, unsigned long long int line) {
	if (err == CannotOpenFile) {
		printf("%s", CNOF);
	}
	else if (err == AllocMemoryError) {
		printf("%s", AM);
	}
	else if (err == CommandLineMissingArgument) {
		printf("%s", CLAM);
	}
	else if (err == DifinedSectionNameError) {
		printf(errorlocation, path, line);
		printf("%s", DSNE);
	}
	else if (err == UnknowIdentifer) {
		printf(errorlocation, path, line);
		printf("%s", UI);
	}
	else printf("(Unknow Error...)");
}

void print(char* str, unsigned long long int len) {
	for (unsigned long long int i = 0; i < len; i++) printf("%c", str[i]);
}