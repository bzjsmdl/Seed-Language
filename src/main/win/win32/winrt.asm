section .text
    global malloc, print, Wprint
    extern _VirtualAlloc@16, _WriteConsoleA@20, _GetStdHandle@4, _WriteConsoleW@20
    malloc:
        push ebp
        mov ebp, esp
        push 0x04
        push 0x3000
        push dword [ebp + 8]
        push 0
        call _VirtualAlloc@16
        test eax, eax
        jne .return
        .error:
            xor eax, eax
        .return:
            pop ebp
            ret 4
    print:
        push ebp
        mov ebp, esp

        push -11
        call _GetStdHandle@4
        test eax, eax
        je .error
        
        push 0
        push 0
        push dword [ebp + 8]
        push dword [ebp + 12]
        push eax
        call _WriteConsoleA@20

        .error:
            xor eax, eax

        pop ebp
        ret 8
    Wprint:
        push ebp
        mov ebp, esp

        push -11
        call _GetStdHandle@4
        test eax, eax
        je .error
        
        push 0
        push 0
        push dword [ebp + 8]
        push dword [ebp + 12]
        push eax
        call _WriteConsoleW@20

        .error:
            xor eax, eax

        pop ebp
        ret 8