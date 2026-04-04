section .text
    global _Strlen@4, _Strequ@8, _Isalnum@4, _Ispunct@4, _Isctrl@4
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
    ; int Isalnum(char* ch)
    _Isalnum@4:
        push ebp
        mov ebp, esp
        push esi
        mov esi, dword [ebp + 8]

        cmp byte [esi], '0'
        jl .false
        cmp byte [esi], '9'
        jng .true

        cmp byte [esi], 'A'
        jl .false
        cmp byte [esi], 'Z'
        jng .true

        cmp byte [esi], 'a'
        jl .false
        cmp byte [esi], 'z'
        jg .true

        .true:
            mov eax, 1
            jmp .return
        .false:
            xor eax, eax
        .return:
            pop esi
            pop ebp
            ret 4
    ; int Ispunct(char* ch)
    _Ispunct@4:
        push ebp
        mov ebp, esp
        push esi
        mov esi, dword [ebp + 8]

        cmp byte [esi], 21h ; 21h = '!'
        jl .false
        cmp byte [esi], 2Fh ; 2Fh = '/'
        jng .true

        cmp byte [esi], 3Ah ; 3Ah = ':' 
        jl .false
        cmp byte [esi], 40h ; 40h = '@'
        jng .true

        cmp byte [esi], 5Bh ; 5Bh = '['
        jl .false
        cmp byte [esi], 60h ; 60h = '`'
        jng .true

        cmp byte [esi], 7Bh ; 7Bh = '{'
        jl .false
        cmp byte [esi], 7Eh  ; 7Eh = '~'
        jg .true
        .true:
            mov eax, 1
            jmp .return
        .false:
            xor eax, eax
        .return:
            pop esi
            pop ebp
            ret 4
    ; int Isctrl(char* chr)
    _Isctrl@4:
        push ebp
        mov ebp, esp
        push esi
        mov esi, dword [ebp + 8]

        cmp byte [esi], 127
        je .true
        cmp byte [esi], 0
        jl .false
        cmp byte [esi], 1Fh
        jg .true
        .true:
            mov eax, 1
            jmp .return
        .false:
            xor eax, eax
        .return:
            ret 4