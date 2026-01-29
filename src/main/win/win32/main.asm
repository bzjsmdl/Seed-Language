section .data
    path_lengh dd 0
    file_lengh dd 0

section .bss
    hOut resd 1
    hIn resd 1
    hErr resd 1
    hFile resd 1
    path resd 257
    Command_Line_Pointer resd 1
    cmdll resd 1   ;Command Line Lengh
    
section .text
    global _main
    extern _GetStdHandle@4, _WriteConsoleA@20, _ExitProcess@4, _ReadConsoleA@20, _CloseHandle@4
    extern _CreateFileA@28, _ReadFile@20, _VirtualAlloc@16, _GetCommandLineW@0
    extern _CommandLineToArgvW@8
    extern malloc, print
    extern strlen, clap
    extern help, help_lengh
    _main:
        .init:
            push -11
            call _GetStdHandle@4
            test eax, eax
            je .error
            mov dword [hOut], eax

            push -10
            call _GetStdHandle@4
            test eax, eax
            je .error
            mov dword [hIn], eax

            push -12
            call _GetStdHandle@4
            test eax, eax
            je .error
            mov dword [hErr], eax
        .cmdl:
            call _GetCommandLineW@0
            mov esi, eax

            push cmdll
            push esi
            call _CommandLineToArgvW@8
            test eax, eax
            je .error
            mov esi, eax

            cmp dword [cmdll], 1
            je .type_help
            
            push esi
            call clap

            push 0
            call _ExitProcess@4
        .type_help:
            push help
            push help_lengh
            call print
            jmp .error
        .error:
            push 1
            call _ExitProcess@4