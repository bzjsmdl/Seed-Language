section .data
    s db "%s"
section .bss
    state resb 0x4000000
    retptr resd 2
section .text
    global _state@12
    extern Isalpha, Isnum, Ispunct
    extern _scanf, _printf, _malloc
    extern _CTCBSS
    ; char* state(unsigned int length, char* text)
    _state@8:
        push ebp
        mov ebp, esp
        push ecx
        push esi
        push edi
        mov ecx, dword [ebp + 8]
        mov esi, dword [ebp + 12]
        mov edi, state
        mov dword [retptr], edi
        .mainloop:
            



        .return:
            pop edi
            pop esi
            pop ecx
            pop ebp
            ret 8

