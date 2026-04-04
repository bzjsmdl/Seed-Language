#include "include/Main.h"
unsigned int error = NoError;
int main(int argc, const char** argv) {
    if (argc == 1) {
        help();
        goto Err;
    }
    if (sizeof(void*) != 8 && sizeof(void*) != 4){
        printf(UNSBN);
        goto Err;
    }
    CompilerTable* table = malloc(sizeof(CompilerTable));
    if (table == NULL) goto Err;

    for (int i = 1; i < argc; i++) {
        if (i == 1) table->Target = argv[i];
        else if (i == 2) table->Input_File = argv[i];
        else if (i == 3) table->Output_File = argv[i];
        if (Strequ("-h", argv[i])) help();
    }
    FILE* src = fopen(table->Input_File, "r");
    unsigned long long int length = flen(src);
    char* text = malloc(length + 1);
    fread(text, length, 1, src);
    unsigned char* stateArr = state(text, length);
    if (stateArr == NULL) {
        if (error == AllocMemoryError) printf(AM);    
        goto Err;
    }
    for (int i = 0; i < length; i++){
        if (stateArr[i] == Character) printf("%x : C\n", text[i]);
        else if (stateArr[i] == Delimter) printf("%x : D\n", text[i]);
        else if (stateArr[i] == Special_Delimter) printf("%x : S\n", text[i]);
        else if (stateArr[i] == NotCharacter) printf("%x : N\n", text[i]);
        else goto Err;
    }
        
    noErr:
        free(text);
        free(stateArr);
        return 0;
    Err: return 1;
}
