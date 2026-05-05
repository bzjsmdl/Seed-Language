#include "../include/Main.h"
extern INTSIZE Line;
extern INTSIZE idx;
extern CompilerTable* table;
extern unsigned int err;
extern const char* path;
int generate(char** txt) {
    FILE* output = fopen(table->Output_File, "wb");  
    if (output == NULL) {
        err = CannotOpenFile;
        return 0;
    }
    path = table->Output_File;
    for (INTSIZE i = 0; i < idx - 1;) {
        if (Strequ(txt[i], "sec")) {
            fprintf(output, "section %s\n", txt[i + 1]);
            i += 2;
        }
        else if (Strequ(txt[i], "pub")) {
            fprintf(output, "global %s\n%s:\n", txt[i + 1], txt[i + 1]);
            i += 2;
        }
        else if (Strequ(txt[i], "nop") || Strequ(txt[i], "ret")){ 
            fprintf(output, "%s ", txt[i]);
            i++;
        }
        else if (Strequ(txt[i], "=>")) {
            fprintf(output, "mov %s, %s", txt[i + 1], txt[i - 1]);
            i += 2;
        }
        else if (txt[i][0] == '\n') {
            fprintf(output, "\n");
            i++;
        }
        else {
            i++;
        }
    }
    fclose(output);
    return 1;
}