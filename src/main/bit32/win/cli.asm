section .data
    isSrc dw 1
    isTar dw 2
    isOut dw 3
        ;Option
            global Option_help, CommandLineEnd
            Option_help db '-',0,'h',0,0,0
            CommandLineEnd dw 0
        ;target
        Target_asm db 'a',0,'s',0,'m',0,0,0


    
section .bss
    argv resd 1
    argc resd 1   ;Command Line Lengh
    

section .text
    global cli
    extern _CloseHandle@4
    extern _CreateFileA@28, _ReadFile@20, _VirtualAlloc@16, _GetCommandLineW@0, _WriteFile@20
    extern _CommandLineToArgvW@8, _LocalFree@4
    extern CompilerTable, NL, NULL_Wide_Character, Zero_Wide_Character, char
    extern strlen, clap, wstrequ, wstrlen, printHelp, wstrcpy
    extern malloc, print, Wprint, free, palloc
    cli:
        .init:
            call _GetCommandLineW@0
            mov esi, eax

            push argc
            push esi
            call _CommandLineToArgvW@8
            mov esi, eax
            mov dword [argv], esi

            cmp dword [argv], 1
            je .type_help
            mov ecx, 1
        .parser:
            lea edi, [esi + ecx*4]
            mov edx, dword [edi]

            push edx
            push NULL_Wide_Character
            call wstrequ
            cmp eax, 1
            je .next

            push edx
            push Zero_Wide_Character
            call wstrequ
            cmp eax, 1
            je .next

            cmp ecx, 1
            je .Target
            cmp ecx, 2
            je .sourcefilepath
            cmp ecx, 3
            je .OutputFile
            .Option:
                push edx
                push Option_help
                call wstrequ
                cmp eax, 1
                je .type_help
        .next:
            cmp ecx, dword [argc]
            je .noErr
            inc ecx
            jmp .parser

        .type_help:
            call printHelp
            jmp .noErr
        .sourcefilepath:
            mov dword [CompilerTable], edx
            jmp .next
        .Target:
            push edx
            push Target_asm
            call wstrequ
            cmp eax, 1
            je .asm
            jne .MissingArgumentError
            .asm:
                mov byte [CompilerTable + 8], 2
                jmp .next
        .OutputFile:
            mov dword [CompilerTable + 4], edx
            jmp .next
        .noErr:
            mov eax, 1
            ret
        .MissingArgumentError:
            mov edx, 2
            xor eax, eax
            ret