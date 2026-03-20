;enum CharacterState:
global Character, Delimter, NotCharacter, Special_Delimter
    Character        equ '2'
    Delimter         equ '1'
    Special_Delimter equ '0'
    NotCharacter     equ 'F'
section .data
    global stateArrPtr
    stateArrPtr dd 0

section .text
    global state
    extern file_lengh, src
    extern InvalidCharacterError, UnknowError, AllocMemoryError
    extern isalnum, malloc
    state:
        .init:
            xor ebx, ebx
            xor edx, edx
            push dword [file_lengh]
            call malloc
            test eax, eax
            je .AMErr
            mov edi, eax
            mov esi, dword [src]
            mov ecx, dword [file_lengh]
        .mainLoop:
            .CmpChar:
                cmp byte [esi + ebx], '0'
                jl .CmpDel
                cmp byte [esi + ebx], '9'
                jng .CharBlock

                cmp byte [esi + ebx], 'a'
                jl .CmpDel
                cmp byte [esi + ebx], 'z'
                jng .CharBlock

                cmp byte [esi + ebx], 'A'
                jl .CmpDel
                cmp byte [esi + ebx], 'Z'
                jng .CharBlock
            .CmpDel:
                cmp byte [esi + ebx], 21h
                jl .CmpSD
                cmp byte [esi + ebx], 2Fh
                jng .DelBlock

                cmp byte [esi + ebx], 3Ah
                jl .CmpSD
                cmp byte [esi + ebx], 40h
                jng .DelBlock

                cmp byte [esi + ebx], 5Bh
                jl .CmpSD
                cmp byte [esi + ebx], 60h
                jng .DelBlock

                cmp byte [esi + ebx], 7Bh
                jl .CmpSD
                cmp byte [esi + ebx], 7Eh
                jng .DelBlock
            .CmpSD:
                cmp byte [esi + ebx], 9
                je .SdelBlock
                cmp byte [esi + ebx], 10
                je .SdelBlock
                cmp byte [esi + ebx], 13
                je .SdelBlock
                cmp byte [esi + ebx], ' '
                je .SdelBlock
            .NChar:
                mov byte [edi + ebx], NotCharacter
            .next:
                inc ebx
                loop .mainLoop
        .return:
            mov eax, 1
            xor edx, edx
            mov edi, dword [stateArrPtr]
            ret
        .CharBlock:
            mov byte [edi + ebx], Character
            jmp .next
        .SdelBlock:
            mov byte [edi + ebx], Special_Delimter
            jmp .next
        .DelBlock:
            mov byte [edi + ebx], Delimter
            jmp .next
        .error:
            xor eax, eax
            ret
        .AMErr:
            mov edx, AllocMemoryError
            jmp .error