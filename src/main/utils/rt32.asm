section .text
	global _Strlen@4, _Strequ@8, _Strcpy@12, _Clear@8, _Strchr@12, _Memequ@12 ;outter -> c
	global Isalpha, Isnum, Ispunct ;inner -> Asm
	; int Isalpha(char* ch)
	Isalpha:
		push ebp
		mov ebp, esp
		push esi
		mov esi, dword [ebp + 8]
		mov al, byte [esi]
		cmp al, 'A'
		jl .false
		cmp al, 'Z'
		jng .true
		cmp al, 'a'
		jl .false
		cmp al, 'z'
		jng .true
		.false:
			xor eax, eax
			jmp .return
		.true:
			mov eax, 1	
		.return:
			pop esi
			pop ebp
			ret 4
	; int Isnum(char* ch)
	Isnum:
		push ebp
		mov ebp, esp
		push esi
		mov esi, dword [ebp + 8]
		mov al, byte [esi]
		cmp al, '0'
		jl .false
		cmp al, '9'
		jng .true
		.false:
			xor eax, eax
			jmp .return
		.true:
			mov eax, 1
		.return:
			pop esi
			pop ebp
			ret 4
	; int Ispunct(char* ch)
	Ispunct:
		push ebp
		mov ebp, esp
		push esi
		mov esi, dword [ebp + 8]
		mov al, byte [esi]
		cmp al, '!'
		jl .false
		cmp al, '/'
		jng .true
		cmp al, ':'
		jl .false
		cmp al, '@'
		jng .true
		cmp al, '['
		jl .false
		cmp al, "`"
		jng .true
		cmp al, '{'
		jl .false
		cmp al, "~"
		jng .true
		.false:
			xor eax, eax
			jmp .return
		.true:
			mov eax, 1
		.return:
			pop esi
			pop ebp
			ret 4
	; int Strlen(const char* string)
	_Strlen@4:
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
	; int Strequ(const char* str1, const char* str2)
	_Strequ@8:
		push ebp
		mov ebp, esp
		push esi
		push edi
		push ecx
		mov esi, dword [ebp + 8]
		mov edi, dword [ebp + 12]
		test esi, esi
		je .false
		test edi, edi
		je .false

		push esi
		call _Strlen@4
		mov ecx, eax

		push edi
		call _Strlen@4
		cmp ecx, eax
		jne .false
		cld
		repe cmpsb
		jne .false
		mov eax, 1
		jmp .return
		.false:
			xor eax, eax
		.return:
			pop ecx
			pop edi
			pop esi
			pop ebp
			ret 8
	; void Strcpy(unsigned int length, const char* src, char* dest)
	_Strcpy@12:
		push ebp
		mov ebp, esp
		push ecx
		push edi
		push esi
		mov ecx, dword [ebp + 8]
		mov esi, dword [ebp + 12]
		mov edi, dword [ebp + 16]
		cld
		rep movsb
		pop esi
		pop esi
		pop ecx
		pop ebp
		ret 12
	; void Clear(void* ptr, unsigned int length)
	_Clear@8:
		push ebp
		mov ebp, esp
		push edi
		push ecx
		push eax
		xor eax, eax
		cld
		rep stosb
		pop eax
		pop ecx
		pop edi
		pop ebp
		ret 8
	; unsigned int Strchr(unsigned int count, char* chr, char* str)
	_Strchr@12:
		push ebp
		mov ebp, esp
		push ecx
		push edi
		mov ecx, dword [ebp + 16]
		mov eax, dword [ebp + 12]
		mov edi, dword [ebp +  8]
		mov al, byte [eax]
		cld
		repne scasb
		jne .err
		dec edi
		mov eax, edi
		.return:
			pop edi
			pop ecx
			pop ebp
			ret 12
		.err:
			xor eax, eax
			jmp .return
	; int Memequ(unsigned int length, const char* str1, const char* str2)
	_Memequ@12:
		push ebp
		mov ebp, esp
		push esi
		push edi
		push ecx
		mov esi, dword [ebp + 8]
		mov edi, dword [ebp + 12]
		mov ecx, dword [ebp + 16]
		test esi, esi
		je .false
		test edi, edi
		je .false
		cld
		repe cmpsb
		jne .false
		mov eax, 1
		jmp .return
		.false:
			xor eax, eax
		.return:
			pop ecx
			pop edi
			pop esi
			pop ebp
			ret 16