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
	void PrintError(const char* path, unsigned long long int line);
	void print(char* str, unsigned long long int len);

	// Lexer
		extern int lexer(INTSIZE length, char* text);
	// Precompiler
		void ClearText(INTSIZE length, char* text);
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
	UnkownBinary,
	UnkownHexadecimal,
};

enum FatherType {
	Keyword,
	Identifer,
	Separator,
	Data
};
enum ChildType {
	a,

	Preprocess_Directive,
	Placeholder,
	Attribute,

	String,

	SSection,
	DSection,
	Section,

	LocalLabel,
	GlobalLabel,
	InnerLabel,
	SuffixLabel,
	Label,

	Pointer,

	ArithmeticOperator,
	LogicalOperator,
	MoveOperator,
	NowPtrDel,

	Hex,
	Bin,
	Dec,
	Oct
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
		#define errorlocation "(In %s:%llu)\n"
		extern char* AM;
		extern char* CNOF;
		extern char* CLAM;
		extern char* DSNE;
		extern char* UI;
		extern char* chelp;
		extern char* BFW;
		extern char* MCQ;
		extern char* UB;
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
	
	#define isSec(str, len) (Memequ(len, str, ".text") || Memequ(len, str, ".data") || Memequ(len, str, ".bss") || Memequ(len, str, ".rdata"))
	#define isReg8(str, len) (Memequ(len, str, "al") || Memequ(len, str, "bl") || Memequ(len, str, "cl") || Memequ(len, str, "dl") || Memequ(len, str, "ah") || Memequ(len, str, "bh") || Memequ(len, str, "ch") || Memequ(len, str, "dh"))
	#define isReg16(str, len) (Memequ(len, str, "ax") || Memequ(len, str, "bx") || Memequ(len, str, "cx") || Memequ(len, str, "dx") || Memequ(len, str, "sp") || Memequ(len, str, "ss") || Memequ(len, str, "ds") || Memequ(len, str, "es") || Memequ(len, str, "fs") || Memequ(len, str, "gs") || Memequ(len, str, "si") || Memequ(len, str, "di") || Memequ(len, str, "bp"))
	#define isReg32(str, len) (Memequ(len, str, "eax") || Memequ(len, str, "ebx") || Memequ(len, str, "ecx") || Memequ(len, str, "edx") || Memequ(len, str, "esi") || Memequ(len, str, "edi") || Memequ(len, str, "esp") || Memequ(len, str, "ebp") || Memequ(len, str, "ax") || Memequ(len, str, "bx") || Memequ(len, str, "cx") || Memequ(len, str, "dx"))
	#define isReg64(str, len) (Memequ(len, str, "sil") || Memequ(len, str, "dil") || Memequ(len, str, "bpl") || Memequ(len, str, "spl") || Memequ(len, str, "r8b") || Memequ(len, str, "r9b") || Memequ(len, str, "r10b") || Memequ(len, str, "r11b") || Memequ(len, str, "r12b") || Memequ(len, str, "r13b") || Memequ(len, str, "r14b") || Memequ(len, str, "r15b")\
							  || Memequ(len, str, "rax") || Memequ(len, str, "rbx") || Memequ(len, str, "rcx") || Memequ(len, str, "rdx") || Memequ(len, str, "rsp")  || Memequ(len, str, "rsi") || Memequ(len, str, "rdi") || Memequ(len, str, "rbp")\
							  || Memequ(len, str, "r8w") || Memequ(len, str, "r9w") || Memequ(len, str, "r10w") || Memequ(len, str, "r11w") || Memequ(len, str, "r12w") || Memequ(len, str, "r13w") || Memequ(len, str, "r14w") || Memequ(len, str, "r15w")\
							  || Memequ(len, str, "r8d") || Memequ(len, str, "r9d") || Memequ(len, str, "r10d") || Memequ(len, str, "r11d") || Memequ(len, str, "r12d") || Memequ(len, str, "r13d") || Memequ(len, str, "r14d") || Memequ(len, str, "r15d"))
	#define isReg(str, len) (isReg8(str, len) || isReg8(str, len) || isReg8(str, len) || isReg8(str, len))
	#define isKeyword(str, len) (Memequ(len, str, "sec") || Memequ(len, str, "pub") || Memequ(len, str, "loc") || Memequ(len, str, "priv")\
								 || Memequ(len, str, "nop") || Memequ(len, str, "cmp") || Memequ(len, str, "je") || Memequ(len, str, "jmp") || Memequ(len, str, "loop")\
								 || Memequ(len, str, "byte") || Memequ(len, str, "word") || Memequ(len, str, "dword") || Memequ(len, str, "qword") || Memequ(len, str, "%%data")\
								 || Memequ(len, str, "#macro"))
#endif