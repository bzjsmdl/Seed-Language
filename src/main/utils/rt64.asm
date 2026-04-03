section .text
    global Strlen, Strequ, Isalnum, Ispunct
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
    ; int Isalnum(char* ch)
    Isalnum:
        cmp byte [rcx], '0'
        jl .false
        cmp byte [rcx], '9'
        jng .true

        cmp byte [rcx], 'A'
        jl .false
        cmp byte [rcx], 'Z'
        jng .true

        cmp byte [rcx], 'a'
        jl .false
        cmp byte [rcx], 'z'
        jng .true

        .true:
            mov eax, 1
            jmp .return
        .false:
            xor eax, eax
        .return:
            ret
    ; int Ispunct(char* ch)
    Ispunct:
        cmp byte [rcx], 21h ; 21h = '!'
        jl .false
        cmp byte [rcx], 2Fh ; 2Fh = '/'
        jng .true

        cmp byte [rcx], 3Ah ; 3Ah = ':' 
        jl .false
        cmp byte [rcx], 40h ; 40h = '@'
        jng .true

        cmp byte [rcx], 5Bh ; 5Bh = '['
        jl .false
        cmp byte [rcx], 60h ; 60h = '`'
        jng .true

        cmp byte [rcx], 7Bh ; 7Bh = '{'
        jl .false
        cmp byte [rcx], 7Eh  ; 7Eh = '~'
        jng .true
        .true:
            mov eax, 1
            jmp .return
        .false:
            xor eax, eax
        .return:
            ret