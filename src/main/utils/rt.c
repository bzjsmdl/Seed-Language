#include "../include/Main.h"
extern unsigned int err;
void help() {
	printf("%s", chelp);
}

INTSIZE flen(FILE* src) {
	INTSIZE length = 0;
	fseek(src, 0, SEEK_END);
	length = ftell(src);
	fseek(src, 0, SEEK_SET);
	return length;
}

void PrintError(const char* path, INTSIZE line) {
	if (err == CannotOpenFile) {
		printf("%s", CNOF);
		printf("(Path: %s)\n", path);
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
	else if (err == BigFileWarnning) {
		printf("%s", BFW);
	}
	else if (err == MissingClosingQuote) {
		printf(errorlocation, path, line);
		printf("%s", MCQ);
	}
	else if (err = InvalidTypeGroup) {
		printf(errorlocation, path, line);
		printf("%s", ITG);
	}
	else if (err == UnkownBinary) {
		printf(errorlocation, path, line);
		printf("%s", UB);
	}
	else if (err = UnkownToken) {
		printf(errorlocation, path, line);
		printf("%s", UT);
	}
	else if (err = UnkownHexadecimal) {
		printf(errorlocation, path, line);
		printf("%s", UH);
	}
	else printf("(Unknow Error...)");
}

void print(char* str, INTSIZE len) {
	for (unsigned long long int i = 0; i < len; i++) printf("%c", str[i]);
}

int IsKeyword(char* str) {
	return (isKeyword(str));
}

int IsSep(char* str) {
	return (isSep(str));
}

int IsReg(char* str) {
	return (isReg(str));
}
