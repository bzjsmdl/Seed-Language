;enum CharacterState:
    Character        equ '2'
    Delimter         equ '1'
    Special_Delimter equ '0'
section .text
    global state
    extern file_lengh, src
    extern InvalidCharacterError, UnknowError
    extern isalnum, malloc
    state:
        .init:
            xor ebx, ebx
            xor edx, edx
            push dword [file_lengh]
            call malloc
            test eax, eax
            je .error
            mov edi, eax
            mov esi, dword [src]
            mov ecx, dword [file_lengh]
        .mainLoop:
            mov al, byte [esi + ebx]
                .CmpChar:
                    cmp al, '0'
                    jle .CmpDel
                    cmp al, '9'
                    jng .CharBlock

                    cmp al, 'a'
                    jle .CmpDel
                    cmp al, 'z'
                    jng .CharBlock

                    cmp al, 'A'
                    jle .CmpDel
                    cmp al, 'Z'
                    jng .CharBlock
                .CmpDel:
                    mov byte [edi + ebx], Special_Delimter
            .next:
                inc ebx
                loop .mainLoop
        .CharBlock:
            mov byte [edi + ebx], Character
            jmp .next
        .return:
            mov eax, 1
            xor edx, edx
            ret
        .error:
            xor eax, eax
            mov edx, UnknowError
            ret