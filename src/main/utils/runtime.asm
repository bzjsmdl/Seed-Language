section .text
    global strlen, clap, wstrequ, wstrlen
    extern malloc, print
    extern help, help_lengh, format, format_lengh, file, file_lengh, target, target_lengh, output, output_lengh
    extern Output_File_Info, Input_File, Option
    extern Option_help
    ;int wstrequ(char* Wdest, const char* Wsrc)
    wstrequ:
        push ebp
        mov ebp, esp
        push esi
        push edi
        push ebx
        push ecx
        mov esi, dword [ebp + 12]   ;Wsrc
        mov edi, dword [ebp + 8]  ;Wdest

        push esi
        call wstrlen
        mov ebx, eax

        push edi
        call wstrlen
        cmp ebx, eax
        jne .false
        mov ecx, eax
        cld
        repe cmpsw
        je .false
        mov eax, 1
        jmp .return
        .false:
            mov eax, -1
        .return:
            pop edi
            pop edi
            ret 8

    ;int wstrlen(const char* Wstring)
    wstrlen:
        push ebp
        mov ebp, esp
        push edi
        mov edi, dword [ebp + 8]
        xor eax, eax
        .c:
            cmp word [edi + eax], 0
            je .return
            add eax, 2
            jmp .c
        .return:
            push ebx
            mov ebx, 2
            div ebx
            pop ebx
            pop edi
            pop ebp
            ret 4

    ;int strlen(const char* string)
    strlen:
        push ebp
        mov ebp, esp
        push edi
        mov edi, dword [ebp + 8]
        xor eax, eax
        .c:
            cmp byte [edi + eax], 0
            je .return
            inc eax
            jmp .c
        .return:
            pop edi
            pop ebp
            ret 4

    ;void clap(const char* argv[], int argc)   //clap = Command Line Arguments Parser
    clap:
        push ebp
        mov ebp,  esp
        push ecx
        push esi
        push edi
        push edx
        mov esi, dword [ebp + 8]
        mov ecx, dword [ebp + 12]
        xor edx, edx

        .parser:
            mov edi, dword [esi]
            .arg:
                push edi 
                push Option_help
                call wstrequ
                cmp eax, 1
                je .Help
            .next:
                inc esi
                loop .parser

        .Help:
            push format
            push format_lengh
            call print

            push file
            push file_lengh
            call print

            push target
            push target_lengh
            call print

            push output
            push output_lengh
            call print

            jmp .return
        .return:
            pop edx
            pop edi
            pop esi
            pop ecx
            pop ebp
            ret 8
