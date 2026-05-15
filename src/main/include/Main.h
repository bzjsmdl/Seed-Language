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
	typedef signed int SINT;
	#define IU "%u"
#elif __SIZEOF_POINTER__ == 8
	typedef unsigned long long int INTSIZE;
	typedef signed long long int SINT;
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
	INTSIZE Pow(INTSIZE a, INTSIZE b);
	int IsMSep(char* str);

	// Lexer
		int lexer(INTSIZE length, char* text);
		void Type(char* type);
	// Precompiler
		void ClearText(INTSIZE length, char* text);
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
	SentenceMissTheEnd,
	InvalidArithmetic,
	InvalidOperation
};

enum Type {
	Keyword = 1,
	Identifer,
	Separator,
	Data,
	NewLine,
	Notype
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
						|| Memequ(1, "!", ch) || Memequ(1, "+", ch) || Memequ(1, "-", ch) || Memequ(1, "*", ch) || Memequ(1, "/", ch)\
						|| Memequ(1, "^", ch))
	#define isLLO(ch) (Memequ(2, "&&", ch) || Memequ(2, "||", ch))
	#define isSep(ch) (isdsep(ch) || istsep(ch) || isACO(ch) || isLLO(ch) || Memequ(1, "{", ch) || Memequ(1, "}", ch)\
					  || Memequ(1, "[", ch) || Memequ(1, "]", ch) || Memequ(1, ">", ch) || Memequ(1, "<", ch) \
					  || Memequ(1, "~", ch) || Memequ(1, ch, ","))
	
	#define isSec(str) (Memequ(5, str, ".text") || Memequ(5, str, ".data") || Memequ(4, str, ".bss") || Memequ(6, str, ".rdata"))
	#define isType(str) (Strequ(str, "byte") || Strequ(str, "word") || Strequ(str, "dword") || Strequ(str, "qword"))
#endif