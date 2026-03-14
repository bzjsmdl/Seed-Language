section .data
    global file_lengh, src
    file_lengh dd 0
    file_lengh_Copy dd 0
    error dd 0
    src dd 0
    cliPtr dd 0
    wsad db "%d",13, 10, 0
    
section .bss
    hOut resd 1
    hIn resd 1
    hErr resd 1
    InFile resd 1
    OutFile resd 1

section .text
    global _main
    extern _GetStdHandle@4, _WriteConsoleA@20, _ExitProcess@4, _ReadConsoleA@20, _CloseHandle@4, _GetLastError@0
    extern _CreateFileW@28, _ReadFile@20, _VirtualAlloc@16, _GetCommandLineW@0, _WriteFile@20, _FormatMessageW@28
    extern _LocalFree@4, _CreateFileMappingW@24, _GetFileSize@8, _printf
    extern NL, CompilerTable, char
    extern strlen, clap, wstrequ, wstrlen, printHelp
    extern malloc, print, Wprint, fopen
    extern cli, state
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
        .cli:
            call cli
            test eax, eax
            je .error
            mov dword [cliPtr], edi

            push 0
            push 0x80
            push 1
            push 0
            push 0
            push 0xC0000000
            push dword [CompilerTable+4]
            call _CreateFileW@28
            cmp eax, -1
            jne .l1
            push 0x80
            push dword [CompilerTable+4]
            call fopen
            cmp eax, -1
            je .error
            .l1: mov dword [OutFile], eax

            push 0
            push 0x80
            push 3
            push 0
            push 0
            push 0xC0000000
            push dword [CompilerTable]
            call _CreateFileW@28
            cmp eax, -1
            je .error
            mov dword [InFile], eax
        .readInputFile:
            push 0
            push dword [InFile]
            call _GetFileSize@8
            cmp eax, -1
            je .error
            mov dword [file_lengh], eax

            push 0x04
            push 0x3000
            push dword [file_lengh]
            push 0
            call _VirtualAlloc@16
            test eax, eax
            je .error
            mov esi, eax
            mov dword [src], esi

            push 0
            push file_lengh_Copy
            push dword [file_lengh]
            push esi
            push dword [InFile]
            call _ReadFile@20
            test eax, eax
            je .error
        
        .main:
            call state
            test eax, eax
            je .error

            push edi
            push dword [file_lengh]
            call print

        .no_error:
            push dword [InFile]
            call _CloseHandle@4

            push dword [OutFile]
            call _CloseHandle@4

            push dword [cliPtr]
            call _LocalFree@4

            push 0
            call _ExitProcess@4
        .error:
            call _GetLastError@0
            mov dword [error], eax
            push eax
            push wsad
            call _printf
            add esp, 8
            push edx
            push wsad
            call _printf
            add esp, 8
            .err:
                push dword [InFile]
                call _CloseHandle@4

                push dword [OutFile]
                call _CloseHandle@4
                
                push dword [cliPtr]
                call _LocalFree@4

                push 1
                call _ExitProcess@4