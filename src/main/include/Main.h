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

// Utis
    void help();
    unsigned long long int flen(FILE* src);
    void PrintError();
    void print(char* str, unsigned long long int len);

    // Lexer
        Token* Lexer(unsigned long long int length, char* text);

    // Asm Function
    #if __SIZEOF_POINTER__ == 4
        extern __stdcall int Strlen(const char* string);
        extern __stdcall int Strequ(const char* str1, const char* str2);
        extern _stdcall void Strcpy(unsigned int length, const char* src, char* dest);
        extern __stdcall void Clear(void* ptr, unsigned int length);
        extern __stdcall char* Strchr(unsigned int count, char* chr, char* str);
        extern __stdcall int Memequ(unsigned int length, const char* str1, const char* str2);
    #elif __SIZEOF_POINTER__ == 8
        extern int Strlen(const char* string);
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
    UnknowLacolLabel
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
    // Help
        #define fromat "Fromat: seed <Target> <Input File> <Output File> <Option>\nE.G.: seed win32 a.seed a.asm -h\n\0"
        #define option "-h / --help: To get help\n"
    // ErrorTips
        #define AM "Seed-Language Compiler: Sorry... I throw an error of alloc memory. It's not your fault.\n\
        I have an advice --\n\
        you can try again or delate me...\0"
        #define CNOF "Seed-Language Compiler: Ah! I coan't open the file.\nNote:\
    1. If you didn't create the file or its path, please created it;\
    2. The file may be occupied by another promgram, systam, or network, or the file is currently running;\
    3. More and More..."

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