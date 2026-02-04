section .bss
    hOut resd 1
    hIn resd 1
    hErr resd 1
    hFile resd 1
    path resd 257

section .text
    global _main
    extern _GetStdHandle@4, _WriteConsoleA@20, _ExitProcess@4, _ReadConsoleA@20, _CloseHandle@4
    extern _CreateFileA@28, _ReadFile@20, _VirtualAlloc@16, _GetCommandLineW@0, _WriteFile@20
    extern _CommandLineToArgvW@8, _LocalFree@4
    extern NL, CompilerTable
    extern strlen, clap, wstrequ, wstrlen, printHelp
    extern malloc, print, Wprint
    extern cli
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
        .main:
            call cli
            test eax, eax
            je .no_error

        .no_error:
            push 0
            call _ExitProcess@4
        
        .error:
            push NL
            push 2
            call print
            push 1
            call _ExitProcess@4
