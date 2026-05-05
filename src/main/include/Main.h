#ifndef Seed_Language_Main_H
#define Seed_Language_Main_H

#include <stdio.h>
#include <stdlib.h>

//Structure
typedef struct CompilerTable {
	const char* Path;
	const char* Input_File;
	const char* Output_File;
	const char* Target;
}CompilerTable;

// Type
#if __SIZEOF_POINTER__ == 4
	typedef unsigned int INTSIZE;
	#define IU "%u"
#elif __SIZEOF_POINTER__ == 8
	typedef unsigned long long int INTSIZE;
	#define IU "%llu"
#endif
#define KB(n) n*1024

// Utils Function
	void help();
	INTSIZE flen(FILE* src);
	void PrintError(const char* path, INTSIZE line);
	void print(char* str,INTSIZE len);
	int IsKeyword(char* str);
	int IsSep(char* str);
	int IsReg(char* str);

	// Lexer
		int lexer(INTSIZE length, char* text);
	// Precompiler
		void ClearText(INTSIZE length, char* text);
		extern void Type(char* type);
	// Parser
		int PStype(char* type);
		int PSgrammer(char* type, char** txt);
	// Generate
		int generate(char** txt);
	// Runtime Asm Function
	#if __SIZEOF_POINTER__ == 4
		extern __stdcall unsigned int Strlen(const char* string);
		extern __stdcall int Strequ(const char* str1, const char* str2);
		extern _stdcall void Strcpy(unsigned int length, const char* src, char* dest);
		extern __stdcall void Clear(void* ptr, unsigned int length);
		extern __stdcall char* Strchr(unsigned int count, char* chr, char* str, int direction);
		extern __stdcall int Memequ(unsigned int length, const char* str1, const char* str2);
		extern __stdcall int Strcat(const char* src, char* dest);
		extern __stdcall int Isalpha(char* ch);
		extern __stdcall int Isnum(char* ch);
		extern __stdcall int Ispunct(char* ch);
	#elif __SIZEOF_POINTER__ == 8
		extern unsigned int Strlen(const char* string);
		extern int Strequ(const char* str1, const char* str2);
		extern void Strcpy(unsigned int length, const char* src, char* dest);
		extern  void clear(unsigned long long int length, void* ptr);
		#define Clear(ptr, length) clear(length, ptr)
		extern char* Strchr(unsigned int count, char* chr, char* str, int direction);
		extern int Memequ(unsigned long long int length, const char* str1, const char* str2);
		extern int Strcat(const char* src, char* dest);
		extern int Isalpha(char* ch);
		extern int Isnum(char* ch);
		extern int Ispunct(char* ch);
	#endif

// Const
enum derection {
	Positive,
	Negative	
};
enum error {
	NoError,
	CommandLineMissingArgument,
	AllocMemoryError,
	CannotOpenFile,
	DifinedSectionNameError,
	UnknowIdentifer,
	BigFileWarnning,
	MissingClosingQuote,
	UnkownBinary,  // UnknowBinary
	UnkownHexadecimal, //UnkownHexadecimal
	UnkownToken, // UnknowToken
	InvalidTypeGroup,
	DefinedSectionOrLabelError,
	KeywordMissingAruments,
	MissingClosingBrace,
	SentenceMissTheEnd
};

enum Type {
	Keyword,
	Identifer,
	Separator,
	Data,
	NewLine
};

enum CharacterState {
	Character,
	Delimter,
	Quote,
	Number,
	NotCharacter
};

// Info
	// ErrorTips
	#if  __SIZEOF_POINTER__ == 8
		#define errorlocation "(In %s:%llu)\n"
	#elif  __SIZEOF_POINTER__ == 4
		#define errorlocation "(In %s:%u)\n"
	#endif
		extern char* AM;
		extern char* CNOF;
		extern char* CLAM;
		extern char* DSNE;
		extern char* UI;
		extern char* chelp;
		extern char* BFW;
		extern char* MCQ;
		extern char* UB;
		extern char* UT;
		extern char* UH;
		extern char* ITG;
		extern char* DSE;
// Macro
	//      istsep(strptr)
	#define isdsep(ch) (Memequ(2, "=>", ch) || Memequ(2, "%%", ch) || Memequ(2, "<<", ch) || Memequ(2, ">>", ch) || Memequ(2, "&&", ch) || Memequ(2, "$$", ch))
	//      istsep(strptr)
	#define istsep(ch) (Memequ(3, "<^<", ch) || Memequ(3, ">&>", ch) || Memequ(3, ">->", ch) || Memequ(3, "<-<", ch)\
						|| Memequ(3, ">^>", ch) || Memequ(3, "<&<", ch) || Memequ(3, "<^<", ch))
	#define isACO(ch) (istsep(ch) || Memequ(2, "<<", ch) || Memequ(2, ">>", ch) || Memequ(1, "&", ch) || Memequ(1, "|", ch)\
						|| Memequ(1, "~", ch) || Memequ(1, "+", ch) || Memequ(1, "-", ch) || Memequ(1, "*", ch) || Memequ(1, "/", ch)\
						|| Memequ(1, "^", ch))
	#define isLLO(ch) (Memequ(2, "&&", ch) || Memequ(2, "||", ch))
	#define isSep(ch) (isdsep(ch) || istsep(ch) || isACO(ch) || isLLO(ch) || Memequ(1, "{", ch) || Memequ(1, "}", ch)\
					  || Memequ(1, "[", ch) || Memequ(1, "]", ch) || Memequ(1, ">", ch) || Memequ(1, "<", ch) || Memequ(1, ";", ch))
	
	#define isSec(str) (Memequ(5, str, ".text") || Memequ(5, str, ".data") || Memequ(4, str, ".bss") || Memequ(6, str, ".rdata"))
	#define isReg8(str) (Memequ(2, str, "al") || Memequ(2, str, "bl") || Memequ(2, str, "cl") || Memequ(2, str, "dl") || Memequ(2, str, "ah") || Memequ(2, str, "bh") || Memequ(2, str, "ch") || Memequ(2, str, "dh"))
	#define isReg16(str) (Memequ(2, str, "ax") || Memequ(2, str, "bx") || Memequ(2, str, "cx") || Memequ(2, str, "dx") || Memequ(2, str, "sp") || Memequ(2, str, "ss") || Memequ(2, str, "ds") || Memequ(2, str, "es") || Memequ(2, str, "fs") || Memequ(2, str, "gs") || Memequ(2, str, "si") || Memequ(2, str, "di") || Memequ(2, str, "bp"))
	#define isReg32(str) (Memequ(3, str, "eax") || Memequ(3, str, "ebx") || Memequ(3, str, "ecx") || Memequ(3, str, "edx") || Memequ(3, str, "esi") || Memequ(3, str, "edi") || Memequ(3, str, "esp") || Memequ(3, str, "ebp"))
	#define isReg64(str) (Memequ(3, str, "sil") || Memequ(3, str, "dil") || Memequ(3, str, "bpl") || Memequ(3, str, "spl") || Memequ(3, str, "r8b") || Memequ(3, str, "r9b") || Memequ(4, str, "r10b") || Memequ(4, str, "r11b") || Memequ(4, str, "r12b") || Memequ(4, str, "r13b") || Memequ(4, str, "r14b") || Memequ(4, str, "r15b")\
							  || Memequ(3, str, "rax") || Memequ(3, str, "rbx") || Memequ(3, str, "rcx") || Memequ(3, str, "rdx") || Memequ(3, str, "rsp")  || Memequ(3, str, "rsi") || Memequ(3, str, "rdi") || Memequ(3, str, "rbp")\
							  || Memequ(3, str, "r8w") || Memequ(3, str, "r9w") || Memequ(4, str, "r10w") || Memequ(4, str, "r11w") || Memequ(4, str, "r12w") || Memequ(4, str, "r13w") || Memequ(4, str, "r14w") || Memequ(4, str, "r15w")\
							  || Memequ(3, str, "r8d") || Memequ(3, str, "r9d") || Memequ(4, str, "r10d") || Memequ(4, str, "r11d") || Memequ(4, str, "r12d") || Memequ(4, str, "r13d") || Memequ(4, str, "r14d") || Memequ(4, str, "r15d"))
	#define isReg(str) (isReg8(str) || isReg16(str) || isReg32(str) || isReg64(str))
	#define isKeyword(str) (Memequ(3, str, "sec") || Memequ(3, str, "pub") || Memequ(3, str, "loc") || Memequ(4, str, "priv")\
			|| Memequ(3, str, "nop") || Memequ(3, str, "cmp") || Memequ(2, str, "je") || Memequ(3, str, "jmp") || Memequ(4, str, "loop")\
			|| Strequ(str ,"rep") || Strequ("cpy", str)\
			|| Memequ(4, str, "byte") || Memequ(4, str, "word") || Memequ(5, str, "dword") || Memequ(5, str, "qword") || Memequ(6, str, "%%data")\
			|| Memequ(6, str, "#macro"))
#endif