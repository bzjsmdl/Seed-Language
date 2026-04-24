section .text
	global Strlen, Strequ, Strcpy, clear, Strchr, Memequ ;outter -> C
	global Isalpha, Isnum, Ispunct ;inner -> Asm
	; int Isalpha(char* ch)
	Isalpha:
		mov al, byte [rcx]
		cmp al, 'A'
		jl .false
		cmp al 'Z'
		jng .true
		cmp al, 'a'
		jl .false
		cmp al 'z'
		jng .true
		.false:
			xor eax, eax
			jmp .return
		.true:
			mov eax, 1	
		.return:
			ret
	; int Isnum(char* ch)
	Isnum:
		mov al, byte [rcx]
		cmp al, '0'
		jl .false
		cmp al '9'
		jng .true
		.false:
			xor eax, eax
			jmp .return
		.true:
			mov eax, 1
		.return:
			ret
	; int Ispunct(char* ch)
	Ispunct:
		mov al, byte [rcx]
		cmp al, '!'
		jl .false
		cmp al '/'
		jng .true
		cmp al, ':'
		jl .false
		cmp al '@'
		jng .true
		cmp al, '['
		jl .false
		cmp al "`"
		jng .true
		cmp al, '{'
		jl .false
		cmp al "~"
		jng .true
		.false:
			xor eax, eax
			jmp .return
		.true:
			mov eax, 1
		.return:
			ret
	; int Strlen(const char* string)
	Strlen:
		xor rax, rax
		.c:
			cmp byte [rcx + rax], 0
			je .return
			inc rax
			jmp .c
		.return:
			ret
	; int Strequ(const char* str1, const char* str2)
	Strequ:
		push rdi
		push rsi
		mov rsi, rcx
		mov rdi, rdx
		test rsi, rsi
		je .false
		test rdi, rdi
		je .false

		mov rcx, rsi
		call Strlen
		mov rcx, rax
		push rcx

		mov rcx, rdi
		call Strlen
		pop rcx
		cmp rcx, rax
		jne .false
		cld
		repe cmpsb
		jne .false
		mov rax, 1
		jmp .return
		.false:
			xor rax, rax
		.return:
			pop rdi
			pop rsi
			ret
	; void Strcpy(unsigned int length, const char* src, char* dest)
	Strcpy:
		push rsi
		push rdi
		mov rsi, rdx
		mov rdi, r8
		cld
		rep movsb
		pop rdi
		pop rsi
		ret 
	; void clear(unsigned int length, void* ptr)
	clear:
		push rdi
		push rax
		mov rdi, rdx
		xor eax, eax
		cld
		rep stosb
		pop rax
		pop rdi
		ret
	; unsigned long long int Strchr(unsigned long long int count, char* chr, char* str)
	Strchr:
		push rdi
		mov al, byte [rdx]
		mov rdi, r8
		cld
		repne scasb
		jne .err
		dec rdi
		mov rax, rdi
		.return:
			pop rdi
			ret
		.err:
			xor rax, rax
			jmp .return
	; int Memequ(unsigned long long int length, const char* str1, const char* str2)
	Memequ:
		push rsi
		push rdi
		mov rsi, rdx
		mov rdi, r8
		test rsi, rsi
		je .false
		test rdi, rdi
		je .false
		cld
		repe cmpsb
		jne .false
		mov rax, 1
		jmp .return
		.false:
			xor rax, rax
		.return:
			pop rdi
			pop rsi
			ret