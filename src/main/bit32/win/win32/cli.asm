section .data
    isSrc dw 1
    isTar dw 2
    isOut dw 3
        ;Option
            global Option_help, CommandLineEnd, Option_output, Option_read, Option_target
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
    extern CompilerTable, NL
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
        
            cmp dword [argc], 1
            je .type_help
            mov ecx, 1
        .parser:
            lea edi, [esi + ecx*4]
            mov edx, dword [edi]
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
            jmp .return
        .sourcefilepath:
            cmp word [edx], 0000h
            je .next
            cmp word [edx], 0030h
            je .next

            push edx
            call wstrlen

            push eax
            call malloc
            mov dword [CompilerTable], eax

            push eax
            push edx
            call wstrcpy
            test eax, eax
            je .CopyFailError
            jmp .next
        .Target:
            cmp word [edx], 0000h
            je .next
            cmp word [edx], 0030h
            je .next

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
            cmp word [edx], 0000h
            je .next
            cmp word [edx], 0030h
            je .next

            push edx
            call wstrlen

            push eax
            call malloc
            mov dword [CompilerTable + 4], eax

            push eax
            push edx
            call wstrcpy
            test eax, eax
            je .CopyFailError 
            jmp .next
        .return:
            push edi
            call _LocalFree@4
            ret
        .noErr:
            xor eax, eax
            jmp .return
        .MissingArgumentError:
            mov eax, 2
            jmp .return
        .CopyFailError:
            mov eax, 3
            jmp .return