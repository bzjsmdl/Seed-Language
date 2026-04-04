section .text
    global Strlen, Strequ
    ; int Strlen(const char* string)
    Strlen:
        xor rax, rax
        .c:
            cmp byte [rcx + rax], 0
            je .return
            inc rax
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
