#ifndef Seed_Language_Main_H
#define Seed_Language_Main_H

#include <stdio.h>
#include <stdlib.h>
#include "rt.h"

// Asm Function
#if __SIZEOF_POINTER__ == 4
    extern __stdcall int Strlen(const char* string);
    extern __stdcall int Strequ(const char* str1, const char* str2);
#elif __SIZEOF_POINTER__ == 8
    extern int Strlen(const char* string);
    extern int Strequ(const char* str1, const char* str2);
#endif

// Const
enum error {
    NoError,
    CommandLineMissingArgument,
    AllocMemoryError,
    CannotReadFile,
    CannotOpenFile
};

enum CharacterState{
    Special_Delimter,
    Delimter,
    Character,
    NotCharacter
};
//Structure
typedef struct CompilerTable {
    const char* Input_File;
    const char* Output_File;
    const char* Target;
}CompilerTable;

// Info
    // Help
        #define fromat "Fromat: seed <Target> <Input File> <Output File> <Option>\nE.G.: seed win32 a.seed a.asm -h\n\0"
        #define option "-h / --help: To get help\n"
    // ErrorTips
        #define AM "Seed-Language Compiler: Sorry... I throw an error of alloc memory. It's not your fault.\n\
        I have an advice --\n\
        you can try again or delate me...\0"
        #define UNSBN "Seed-Language Compiler: Wh...What? I know 32-bit and 64-bit, but I don't know the bitness."

// Macro
    #define isalnum(ch) ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
    
#endif