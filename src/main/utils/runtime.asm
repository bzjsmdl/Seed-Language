section .text
    global strlen, clap, wstrequ, wstrlen
    extern malloc, print, Wprint
    extern help, help_lengh, format, format_lengh, file, file_lengh, target, target_lengh, output, output_lengh
    extern Output_File_Info, Input_File, Option, NL
    extern Option_help, CommandLineEnd
    ;int wstrequ(char* Wdest, const char* Wsrc)
    wstrequ:
        push ebp
        mov ebp, esp
        push esi
        push edi
        push ecx
        mov esi, dword [ebp + 12]   ;Wsrc
        mov edi, dword [ebp + 8]  ;Wdest

        push esi
        call wstrlen
        mov ecx, eax

        push edi
        call wstrlen
        cmp ecx, eax
        jne .false

        cld
        repe cmpsw
        jne .false

        mov eax, 1
        jmp .return
        .false:
            mov eax, -1
        .return:
            pop ecx
            pop edi
            pop esi
            pop ebp
            ret 8

    ;int wstrlen(const char* Wstring)
    wstrlen:
        push ebp
        mov ebp, esp
        push edi
        mov edi, dword [ebp + 8]
        xor eax, eax
        .c:
            cmp word [edi + eax], 0
            je .return
            add eax, 2
            jmp .c
        .return:
            shr eax, 1
            pop edi
            pop ebp
            ret 4

    ;int strlen(const char* string)
    strlen:
        push ebp
        mov ebp, esp
        push edi
        mov edi, dword [ebp + 8]
        xor eax, eax
        .c:
            cmp byte [edi + eax], 0
            je .return
            inc eax
            jmp .c
        .return:
            pop edi
            pop ebp
            ret 4

    ;void clap(const char* argv[], int argc)   //clap = Command Line Arguments Parser
    clap:
        push ebp
        mov ebp, esp
        push ecx
        push esi
        push edi
        mov esi, dword [ebp + 8]
        mov ecx, dword [ebp + 12]
        inc esi
        dec ecx

        .parser:
            mov edi, dword [esi]
            .arg:
                push edi 
                push Option_help
                call wstrequ
                cmp eax, 1
                je .Help
                jne .error
            .next:
                inc esi
                loop .parser
        jmp .return

        .Help:nop
        .error:
            xor eax, eax
        .return:
            pop edi
            pop esi
            pop ecx
            pop ebp
            ret 8
