#include "include/Main.h"
#include "include/rt.h"
int main(int argc, const char** argv) {
    CompilerTable* table = malloc(sizeof(CompilerTable));
    if (argc == 1) {
        help();
        goto Err;
    }
    for (int i = 1; i < argc; i++) {
        if (i == 1) table->Target = argv[i];
        else if (i == 2) table->Input_File = argv[i];
        else if (i == 3) table->Output_File = argv[i];
        if (sizeof(void*) == 8)
            if (Strequ64("-h", argv[i])) help();
        else if (sizeof(void*) == 4)
            if (Strequ32("-h", argv[i])) help();
        else{
            printf(UNSBN);
            goto Err;
        }
        
    }
    FILE* src = fopen(table->Input_File, "r");
    unsigned long long int length = flen(src);
    char* text = malloc(length + 1);
    fread(text, 0, length, src);
    printf("%s\n", text);

    noErr:
        free(text);
        return 0;
    Err: return 1;
}
