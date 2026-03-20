
section .data
    ;struct ScannerToken:
    ;   char* text        // 4 Bytes
    ;   unsigned int size    // 4 Bytes
    ;   ScannerToken* next   // 4 Bytes
    ScannerTokenSize equ 12   ; 4 + 4 + 4 = 12
    Token_text equ 0
    Token_size equ 4
    Token_next equ 8
    ScannerTokenBase dd 0

section .text
    global scanner
    extern Character, Delimter, NotCharacter, Special_Delimter
    extern InvalidCharacterError, UnknowError, AllocMemoryError
    extern stateArrPtr, file_lengh
    extern malloc
    scanner:
        .init:
            xor ebx, ebx
            xor edx, edx
            mov esi, dword [stateArrPtr]
            mov ecx, dword [file_lengh]
            push ScannerTokenSize
            call malloc
            test eax, eax
            je .AMErr
            mov edi, eax
            mov dword [ScannerTokenBase], edi
        .main:
            mov al, byte [esi + ebx]
            cmp al, 'F'
            je .next
            cmp al, byte [esi + ebx + 1]
            jne .addScannerToken
            inc edx
            .next:
                inc ebx
                loop .main
        .return:
            mov eax, 1
            xor edx, edx
            ret
        .addScannerToken:
            mov dword [edi + Token_size], edx
            
            lea eax, [esi + ebx]
            sub eax, edx
            mov dword [edi + Token_text], eax
            

            push ScannerTokenSize
            call malloc
            test eax, eax
            je .AMErr

            mov dword [edi + Token_next], eax
            mov edi, eax
            jmp .next
            
        .error:
            xor eax, eax
            ret
        .AMErr:
            mov edx, AllocMemoryError
            jmp .error