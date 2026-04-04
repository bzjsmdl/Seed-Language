section .text
    global Strlen, Strequ, Isalnum, Ispunct, Isctrl
    ; int Strlen(const char* string)
    Strlen:
        xor rax, rax
        .c:
            cmp byte [rcx + rax], 0
            je .return
            inc eax
            jmp .c
        .return:
            ret
    ; int Strequ(const char* str1, const char* str2)
    Strequ:
        push rdi
        push rsi
        mov rsi, rcx
        mov rdi, rdx
        test rsi, rsi
        je .false
        test rdi, rdi
        je .false

        mov rcx, rsi
        call Strlen
        mov rcx, rax
        push rcx

        mov rcx, rdi
        call Strlen
        pop rcx
        cmp rcx, rax
        jne .false
        cld
        repe cmpsb
        jne .false
        mov rax, 1
        jmp .return
        .false:
            xor rax, rax
        .return:
            pop rdi
            pop rsi
            ret
    ; int Isalnum(int ch)
    Isalnum:
        cmp cl, '0'
        jl .false
        cmp cl, '9'
        jng .true

        cmp cl, 'A'
        jl .false
        cmp cl, 'Z'
        jng .true

        cmp cl, 'a'
        jl .false
        cmp cl, 'z'
        jg .false

        .true:
            mov rax, 1
            jmp .return
        .false:
            xor rax, rax
        .return:
            ret
    ; int Ispunct(char* ch)
    Ispunct:
        cmp cl, '!'
        jl .false
        cmp cl, '/'
        jng .true

        cmp cl, ':' 
        jl .false
        cmp cl, '@'
        jng .true

        cmp cl, '['
        jl .false
        cmp cl, '`'
        jng .true

        cmp cl, '{'
        jl .false
        cmp cl, '~'
        jg .false
        .true:
            mov rax, 1
            jmp .return
        .false:
            xor rax, rax
        .return:
            ret
    ; int Isctrl(char* chr)
    Isctrl:
        cmp cl, 127
        je .true
        cmp cl, 0
        jl .false
        cmp cl, 1Fh
        jg .false
        .true:
            mov rax, 1
            jmp .return
        .false:
            xor rax, rax
        .return:
            ret