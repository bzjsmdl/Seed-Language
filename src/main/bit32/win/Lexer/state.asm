;enum CharacterState:
    Character        equ '2'
    Delimter         equ '1'
    Special_Delimter equ '0'
section .data
    global TempFile, hTempFile, hTempFileMapping, TempFileMappingName
    extern InvalidCharacterError, UnkownError
    TempFile db "TempFile.temp"
    hTempFile dd 0
    hTempFileMapping dd 0
    TempFileMappingName db "temp"

    Loop_Count dq 0
section .text
    global state
    extern _CreateFileA@28, _CreateFileMappingA@24, _MapViewOfFile@20
    extern file_lengh, src
    extern isalnum, isprint
    state:
        .init:
            push 0
            push 0x80
            push 1
            push 0
            push 0
            push 0xC0000000
            push TempFile
            call _CreateFileA@28
            cmp eax, -1
            je .error
            mov dword [hTempFile], eax

            push TempFileMappingName
            push dword [file_lengh]
            push dword [file_lengh + 4]
            push 0x02
            push 0
            push dword [hTempFile]
            call _CreateFileMappingA@24
            mov dword [hTempFileMapping], eax

            push 0
            push 0
            push 0
            push 0x0004
            push dword [hTempFileMapping]
            call _MapViewOfFile@20
            test eax, eax
            je .error

            xor ebx, ebx
            xor edx, edx
            mov edi, eax
            mov esi, dword [src]
            mov ecx, dword [file_lengh]
            push dword [file_lengh + 4]
        .Outer:
            .Inner:
                lea edx, byte [esi + ebx]
                push edx
                call isprint
                test eax, eax
                je .invalidcharacter

                push edx
                call isalnum
                cmp eax, 1
                je .CharBlock

                cmp al, 9
                je .SDBlock
                cmp al, 10
                je .SDBlock
                cmp al, 13
                je .SDBlock

                mov byte [edi + ebx], Delimter
            .InnerNext:
                inc ebx
                loop .Inner
        .OuterNext:
            pop ecx
            jecxz .return
            dec ecx
            push ecx
            mov ecx, -1
            jmp .Outer

        .CharBlock:
            mov byte [edi + ebx], Character
            jmp .InnerNext
        .SDBlock:
            mov byte [edi + ebx], Special_Delimter
            jmp .InnerNext
        xor eax, eax
        jmp .return
        .invalidcharacter:
            mov eax, InvalidCharacterError
            ret
        .error:
            mov eax, UnkownError
        .return: ret
