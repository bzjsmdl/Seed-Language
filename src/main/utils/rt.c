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
	// if (err == CannotOpenFile) {
	// 	printf("%s", CNOF);
	// 	printf("(Path: %s)\n", path);
	// 	return;
	// }
	// else if (err == AllocMemoryError) {
	// 	printf("%s", AM);
	// 	return;
	// }
	// else if (err == CommandLineMissingArgument) {
	// 	printf("%s", CLAM);
	// 	return;
	// }
	// else if (err == DifinedSectionNameError) {
	// 	printf(errorlocation, path, line);
	// 	printf("%s", DSNE);
	// 	return;
	// }
	// else if (err == UnknowIdentifer) {
	// 	printf(errorlocation, path, line);
	// 	printf("%s", UI);
	// 	return;
	// }
	// else if (err == BigFileWarnning) {
	// 	printf("%s", BFW);
	// 	return;
	// }
	// else if (err == MissingClosingQuote) {
	// 	printf(errorlocation, path, line);
	// 	printf("%s", MCQ);
	// 	return;
	// }
	// else if (err = InvalidTypeGroup) {
	// 	printf(errorlocation, path, line);
	// 	printf("%s", ITG);
	// 	return;
	// }
	// else if (err == UnkownBinary) {
	// 	printf(errorlocation, path, line);
	// 	printf("%s", UB);
	// 	return;
	// }
	// else if (err = UnkownToken) {
	// 	printf(errorlocation, path, line);
	// 	printf("%s", UT);
	// 	return;
	// }
	// else if (err = UnkownHexadecimal) {
	// 	printf(errorlocation, path, line);
	// 	printf("%s", UH);
	// 	return;
	// }
	// else {
	// 	printf("(Unknow Error: %u)", err);
	// 	return;
	// }
	printf(errorlocation "\nErr: %d\n", path, line, err);
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
