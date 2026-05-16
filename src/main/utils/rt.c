#include "../include/Main.h"
extern unsigned int err;
INTSIZE Pow(INTSIZE a, INTSIZE b) {
	INTSIZE p = 1;
	if (b != 0) {
		for (INTSIZE i = 0; i < b; i++) p *= a;
	}
	return p;
}
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
	if (Strequ(str, "loc") || Strequ(str, "pop") || Strequ(str, "push") || Strequ(str, "call") || Strequ(str, "jl") || Strequ(str, "jng") || Strequ(str, "test")) return 1;
	else if (Strequ(str, "sec") || Strequ(str, "pub") || Strequ(str, "priv") || Strequ(str, "res") || Strequ(str, "inc") || Strequ(str, "dec")) return 1;
	else if (Strequ(str ,"rep") || Strequ("cpy", str) || Strequ("ret", str) || Strequ(str, "jne") || Strequ(str ,"repe") || Strequ(str ,"repne")) return 1;
	else if (Strequ(str, "nop") || Strequ(str, "je") || Strequ(str, "jmp") || Strequ(str, "loop") || Strequ(str, "cmp") || Strequ(str, "call")) return 1;
	else if (Strequ(str, "byte") || Strequ(str, "word") || Strequ(str, "dword") || Strequ(str, "qword") || Strequ(str, "%%data") || Strequ(str, "getpd") || Strequ(str, "extern")) return 1;
	else if (Strequ(str, "#macro") || Strequ(str ,"loope") ||Strequ(str ,"loopne") || Strequ(str, "cpy") || Strequ(str, "write") || Strequ(str, "read") || Strequ(str, "find") || Strequ(str, "putpd")) return 1;
	else if (Strequ(str, "jg") || Strequ(str, "jnl") || Strequ(str, "comp") || Strequ(str, "jz") || Strequ(str, "jnz") || Strequ(str, "jna") || Strequ(str, "jnb") || Strequ(str, "jb") || Strequ(str, "ja")) return 1;
	else return 0;
}

int IsSep(char* str) {
	if (Strequ(str, ":") || Strequ(";", str)) return 1;
	else if (Strequ("=>", str) || Strequ("%%", str) || Strequ("<<", str) || Strequ(">>", str)) return 1;
	else if (Strequ("&&", str) || Strequ("$$", str) || Strequ("<^<", str) || Strequ(">&>", str)) return 1;
	else if (Strequ(">->", str) || Strequ("<-<", str) || Strequ(">^>", str) || Strequ("<&<", str)) return 1;
	else if (Strequ("<^<", str) || Strequ("<^<", str) || Strequ(">&>", str) || Strequ(">->", str)) return 1;
	else if (Strequ("<-<", str) || Strequ(">^>", str) || Strequ("<&<", str) || Strequ("<^<", str)) return 1;
	else if (Strequ("<<", str) || Strequ(">>", str) || Strequ("&", str) || Strequ("|", str) || Strequ("!", str) || Strequ("+", str) || Strequ("-", str) || Strequ("*", str) || Strequ("/", str) || Strequ("^", str)) return 1;
	else if (Strequ("&&", str) || Strequ("||", str) || Strequ("{", str) || Strequ("}", str) || Strequ("[", str) || Strequ("]", str) || Strequ(">", str) || Strequ("<", str) || Strequ("~", str) || Strequ(str, ",")) return 1;
	else return 0;
}

int IsMSep(char* Mem) {
	if (Memequ(2, "=>", Mem) || Memequ(2, "%%", Mem) || Memequ(2, "<<", Mem) || Memequ(2, ">>", Mem)) return 1;
	else if (Memequ(2, "&&", Mem) || Memequ(2, "$$", Mem) || Memequ(3, "<^<", Mem) || Memequ(3, ">&>", Mem)) return 1;
	else if (Memequ(3, ">->", Mem) || Memequ(3, "<-<", Mem) || Memequ(3, ">^>", Mem) || Memequ(3, "<&<", Mem)) return 1;
	else if (Memequ(3, "<^<", Mem) || Memequ(3, "<^<", Mem) || Memequ(3, ">&>", Mem) || Memequ(3, ">->", Mem)) return 1;
	else if (Memequ(3, "<-<", Mem) || Memequ(3, ">^>", Mem) || Memequ(3, "<&<", Mem) || Memequ(3, "<^<", Mem)) return 1;
	else if (Memequ(2, "<<", Mem) || Memequ(2, ">>", Mem) || Memequ(2, "&&", Mem) || Memequ(2, "||", Mem)) return 1;
	else return 1;
}

int IsReg(char* str) {
	if (Memequ(2, str, "ax") || Memequ(2, str, "bx") || Memequ(2, str, "cx") || Memequ(2, str, "dx") || Memequ(2, str, "sp") || Memequ(2, str, "ss") || Memequ(2, str, "ds") || Memequ(2, str, "es") || Memequ(2, str, "fs") || Memequ(2, str, "gs") || Memequ(2, str, "si") || Memequ(2, str, "di") || Memequ(2, str, "bp")) return 1;
	else if (Memequ(3, str, "eax") || Memequ(3, str, "ebx") || Memequ(3, str, "ecx") || Memequ(3, str, "edx") || Memequ(3, str, "esi") || Memequ(3, str, "edi") || Memequ(3, str, "esp") || Memequ(3, str, "ebp")) return 1;
	else if (Memequ(2, str, "al") || Memequ(2, str, "bl") || Memequ(2, str, "cl") || Memequ(2, str, "dl") || Memequ(2, str, "ah") || Memequ(2, str, "bh") || Memequ(2, str, "ch") || Memequ(2, str, "dh")) return 1;
	else if (Memequ(3, str, "sil") || Memequ(3, str, "dil") || Memequ(3, str, "bpl") || Memequ(3, str, "spl") || Memequ(3, str, "r8b") || Memequ(3, str, "r9b") || Memequ(4, str, "r10b") || Memequ(4, str, "r11b") || Memequ(4, str, "r12b") || Memequ(4, str, "r13b") || Memequ(4, str, "r14b") || Memequ(4, str, "r15b")\
							  || Memequ(3, str, "rax") || Memequ(3, str, "rbx") || Memequ(3, str, "rcx") || Memequ(3, str, "rdx") || Memequ(3, str, "rsp")  || Memequ(3, str, "rsi") || Memequ(3, str, "rdi") || Memequ(3, str, "rbp")\
							  || Memequ(3, str, "r8w") || Memequ(3, str, "r9w") || Memequ(4, str, "r10w") || Memequ(4, str, "r11w") || Memequ(4, str, "r12w") || Memequ(4, str, "r13w") || Memequ(4, str, "r14w") || Memequ(4, str, "r15w")\
							  || Memequ(3, str, "r8d") || Memequ(3, str, "r9d") || Memequ(4, str, "r10d") || Memequ(4, str, "r11d") || Memequ(4, str, "r12d") || Memequ(4, str, "r13d") || Memequ(4, str, "r14d") || Memequ(4, str, "r15d")) return 1;
	else return (Strequ("df", str) || Strequ("if", str) || Strequ("cf", str) || Strequ("DF", str) || Strequ("IF", str) || Strequ("CF", str) || Strequ("flags", str) || Strequ("eflags", str) || Strequ("rflags", str));
}
