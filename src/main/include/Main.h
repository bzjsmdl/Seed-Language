#ifndef Seed_Language_Main_H
#define Seed_Language_Main_H

#include <stdio.h>
#include <stdlib.h>

//Structure
typedef struct CompilerTable {
	const char* Input_File;
	const char* Output_File;
	const char* Target;
}CompilerTable;

typedef struct token {
	char* texts;
	unsigned long long int len;
	int type;
	unsigned long long int line;
	struct token* next;
}Token;

// Utils Function
	void help();
	unsigned long long int flen(FILE* src);
	void PrintError(const char* path, unsigned long long int line);
	void print(char* str, unsigned long long int len);

	// Lexer
		Token* Lexer(unsigned long long int length, char* text);
		extern char* state(unsigned long long int length, char* text);
		#if __SIZEOF_POINTER__ == 4
			extern __stdcall char* state(unsigned int length, char* text);
		#elif __SIZEOF_POINTER__ == 8
			extern char* state(unsigned long long int length, char* text);
		#endif
	// Runtime Asm Function
	#if __SIZEOF_POINTER__ == 4
		extern __stdcall unsigned int Strlen(const char* string);
		extern __stdcall int Strequ(const char* str1, const char* str2);
		extern _stdcall void Strcpy(unsigned int length, const char* src, char* dest);
		extern __stdcall void Clear(void* ptr, unsigned int length);
		extern __stdcall char* Strchr(unsigned int count, char* chr, char* str);
		extern __stdcall int Memequ(unsigned int length, const char* str1, const char* str2);
	#elif __SIZEOF_POINTER__ == 8
		extern unsigned int Strlen(const char* string);
		extern int Strequ(const char* str1, const char* str2);
		extern void Strcpy(unsigned int length, const char* src, char* dest);
		extern  void clear(unsigned long long int length, void* ptr);
		#define Clear(ptr, length) clear(length, ptr)
		extern char* Strchr(unsigned long long int count, char* chr, char* str);
		extern int Memequ(unsigned long long int length, const char* str1, const char* str2);
	#endif

// Const
enum error {
	NoError,
	CommandLineMissingArgument,
	AllocMemoryError,
	CannotOpenFile,
	DifinedSectionNameError,
	UnknowIdentifer
};

enum ReadTarget{
	Seed,
	IR
};
enum TokenType {
	Keyword,
	Identifer,
	Separator,
	Preprocess_Directive,
	Placeholder,
	Data,
	String,
	Section,
	LocalLabel,
	Attribute
};

enum CharacterState {
	Character,
	Delimter,
	Quote,
	Number,
	NotCharacter,
	Space
};

// Info
	// ErrorTips
		#define errorlocation "(In %s:%llu)\n"
		extern char* AM;
		extern char* CNOF;
		extern char* CLAM;
		extern char* DSNE;
		extern char* UI;
		extern char* chelp;
// Macro
	#define isalpha(ch) ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
	#define isnum(ch) ((ch >= '0' && ch <= '9'))
	#define ispunct(ch) ((ch > ' ' && ch < '0') || (ch > '9' && ch < 'A') || (ch > 'Z' && ch < 'a') || (ch > 'z' && ch < 127))
	#define isKeyword(str, len) (Memequ(len, str, "sec") || Memequ(len, str, "pub") || Memequ(len, str, "nop") || Memequ(len, str, "byte"))
	#define isdsep(ch) ((Memequ(2, "=>", ch) || Memequ(2, "//", ch) || Memequ(2, "/*", ch) || Memequ(2, "*/", ch)))
		   //isdsep(strPtr)
	#define isSdel(ch) (ch == '_' || ch == '.' || ch == '#' || ch == '@' || ch == '%')
	#define isReg16(str, len) (Memequ(len, str, "ax") || Memequ(len, str, "bx") || Memequ(len, str, "cx") || Memequ(len, str, "dx"))
	#define isSec(str, len) (Memequ(len, str, ".text") || Memequ(len, str, ".data") || Memequ(len, str, ".bss") || Memequ(len, str, ".rodata"))
	#define isReg32(str, len) (Memequ(len, str, "eax") || Memequ(len, str, "ebx") || Memequ(len, str, "ecx") || Memequ(len, str, "edx"))
#endif