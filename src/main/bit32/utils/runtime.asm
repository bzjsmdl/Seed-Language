section .text
    global strlen, wstrequ, wstrlen, printHelp, strcpy, wstrcpy
    extern malloc, print, Wprint
    extern help, help_lengh, format, format_lengh, file, file_lengh, target, target_lengh, output, output_lengh
    extern Output_File_Info, Input_File, Option, NL
    extern Option_help, CommandLineEnd, Option_output, Option_read, Option_target
    ;int wstrlen(const char* Wstring)
    wstrlen:
        push ebp
        mov ebp, esp
        push edi
        mov edi, dword [ebp + 8]
        test edi, edi
        je .false
        xor eax, eax
        .wcslen_loop:
            cmp word [edi], 0
            je .return
            add edi, 2
            inc eax
            jmp .wcslen_loop
        jmp .return
        .false:
            xor eax, eax
        .return:
            pop edi
            pop ebp
            ret 4
    ;int wstrequ(const wchar_t* Wstr1, const wchar_t* wstr2)
    wstrequ:
        push ebp
        mov ebp, esp
        push esi
        push edi
        push ecx
        mov esi, dword [ebp + 8]
        mov edi, dword [ebp + 12]
        test esi, esi
        je .false
        test edi, edi
        je .false

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
            xor eax, eax
        .return:
            pop ecx
            pop edi
            pop esi
            pop ebp
            ret 8
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
    ;int strcat(const char* src, char* dest)
    strcat:
        push ebp
        mov ebp, esp
        push esi
        push edi
        push ecx
        mov edi, dword [ebp + 12]
        mov esi, dword [ebp + 8]
        test esi, esi
        je .false
        test edi, edi
        je .false
        push edi
        call strlen
        lea edi, [edi + eax]
        push esi
        call strlen
        mov ecx, eax
        cld
        rep movsb
        mov eax, 1
        jmp .return
        .false:
            xor eax, eax
        .return:
            pop ecx
            pop edi
            pop esi
            pop ebp
            ret 8
    ;void help()
    printHelp:
        push format
        push format_lengh
        call print

        push help
        push help_lengh
        call print
        ret
    ;int strcpy(const char* src, char* dest)
    strcpy:
        push ebp
        mov ebp, esp
        push esi
        push edi
        push ecx
        mov edi, dword [ebp + 12]
        mov esi, dword [ebp + 8]
        test esi, esi
        je .false
        test edi, edi
        je .false
        push esi
        call strlen
        mov ecx, eax
        cld
        rep movsb
        mov eax, 1
        jmp .return
        .false:
            xor eax, eax
        .return:
            pop ecx
            pop edi
            pop esi
            pop ebp
            ret 8
    ;int wstrcpy(const char* src, char* dest)
    wstrcpy:
        push ebp
        mov ebp, esp
        push esi
        push edi
        push ecx
        mov edi, dword [ebp + 12]
        mov esi, dword [ebp + 8]
        test esi, esi
        je .false
        test edi, edi
        je .false
        push esi
        call wstrlen
        mov ecx, eax
        cld
        rep movsw
        mov eax, 1
        jmp .return
        .false:
            xor eax, eax
        .return:
            pop ecx
            pop edi
            pop esi
            pop ebp
            ret 8
    