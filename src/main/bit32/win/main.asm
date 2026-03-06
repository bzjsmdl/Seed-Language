section .data
    global file_lengh, src
    file_lengh dd 0, 0
    ;             l  h
    InputFileMappingName db "Hello ,World!"
    error dd 0
    src dd 0

section .bss
    hOut resd 1
    hIn resd 1
    hErr resd 1
    InFile resd 1
    OutFile resd 1
    hInFileMapping resd 1

section .text
    global _main
    extern _GetStdHandle@4, _WriteConsoleA@20, _ExitProcess@4, _ReadConsoleA@20, _CloseHandle@4, _GetLastError@0
    extern _CreateFileW@28, _ReadFile@20, _VirtualAlloc@16, _GetCommandLineW@0, _WriteFile@20, _FormatMessageW@28
    extern _LocalFree@4, _CreateFileMappingW@24, _GetFileSize@8, _MapViewOfFile@20, _UnmapViewOfFile@4
    extern NL, CompilerTable, char
    extern strlen, clap, wstrequ, wstrlen, printHelp
    extern malloc, print, Wprint
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
            jne .error

            push 0
            push 0x80
            push 4
            push 0
            push 0
            push 0x0C0000000
            push dword [CompilerTable+4]
            call _CreateFileW@28
            cmp eax, -1
            je .error
            mov dword [OutFile], eax

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
            lea edi, [file_lengh + 4]
            push edi
            push dword [InFile]
            call _GetFileSize@8
            mov eax, dword [file_lengh]

            push InputFileMappingName
            push dword [file_lengh]
            push dword [file_lengh + 4]
            push 0x04
            push 0
            push dword [InFile]
            call _CreateFileMappingW@24
            mov dword [hInFileMapping], eax

            push 0
            push 0
            push 0
            push 0x0004
            push dword [hInFileMapping]
            call _MapViewOfFile@20
            test eax, eax
            je .error
            mov esi, eax
            mov dword [src], esi
            
        .main:
            call state
            test eax, eax
            jne .error

            push edi
            push 12
            call print
            
        .no_error:
            push esi
            call _UnmapViewOfFile@4
            
            push dword [hInFileMapping]
            call _CloseHandle@4

            push dword [InFile]
            call _CloseHandle@4

            push dword [OutFile]
            call _CloseHandle@4

            push edi
            call _LocalFree@4

            push 0
            call _ExitProcess@4
        .error:
            call _GetLastError@0
            mov dword [error], eax
            .err:
                push esi
                call _UnmapViewOfFile@4
                
                push dword [hInFileMapping]
                call _CloseHandle@4

                push dword [InFile]
                call _CloseHandle@4

                push dword [OutFile]
                call _CloseHandle@4
                
                push edi
                call _LocalFree@4

                push 1
                call _ExitProcess@4