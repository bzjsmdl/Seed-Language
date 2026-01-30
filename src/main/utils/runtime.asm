section .text
    global strlen, _clap, _wstrequ, wstrlen
    extern malloc, print
    extern help, help_lengh, format, format_lengh, file, file_lengh, target, target_lengh, output, output_lengh
    extern Output_File_Info, Input_File, Option
    extern Option_help, CommandLineEnd
    ;int wstrequ(char* Wdest, const char* Wsrc)
    _wstrequ:
        push ebp
        mov ebp, esp
        push esi
        push edi
        push ebx
        push ecx
        mov esi, dword [ebp + 12]   ;Wsrc
        mov edi, dword [ebp + 8]  ;Wdest

        push esi
        call wstrlen
        mov ebx, eax

        push edi
        call wstrlen
        cmp ebx, eax
        jne .false
        mov ecx, eax

        cld
        repe cmpsw
        jne .false

        mov eax, 1
        jmp .return
        .false:
            mov eax, -1
        .return:
            pop ecx
            pop ebx
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
            push ebx
            mov ebx, 2
            div ebx
            pop ebx
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
    _clap:
        push ebp
        mov ebp,  esp
        push ecx
        push esi
        push edi
        push edx
        mov esi, dword [ebp + 8]
        mov ecx, dword [ebp + 12]
        xor edx, edx

        .parser:
            mov edi, dword [esi]
            push edi 
            push CommandLineEnd
            call _wstrequ
            cmp eax, 1
            je .return
            .arg:
                push edi 
                push Option_help
                call _wstrequ
                cmp eax, 1
                je .Help
                jne .error
            .next:
                inc esi
                loop .parser
        jmp .return

        .Help:
            mov eax, 42
            jmp .return
        .error:
            xor eax, eax
        .return:
            pop edx
            pop edi
            pop esi
            pop ecx
            pop ebp
            ret 8
