section .text
    global _Strlen@4, _Strequ@8
    ; int Strlen(const char* string)
    _Strlen@4:
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
    ; int Strequ(const char* str1, const char* str2)
    _Strequ@8:
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
        call _Strlen@4
        mov ecx, eax

        push edi
        call _Strlen@4
        cmp ecx, eax
        jne .false
        cld
        repe cmpsb
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
