section .data
	s db "%s"
	cf db "%c"
	c db 0
	Character equ 0
	Delimter equ 1
	Quote equ 2
	Number equ 3
	NotCharacter equ 4
	Space equ 5
section .bss
	state resb 0x8000000
section .text
	global _state@8
	extern Isalpha, Isnum, Ispunct
	extern _scanf, _printf
	extern _err, _OK, _BFW, _UN
	; char* state(unsigned int length, char* text)
	_state@8:
		push ebp
		mov ebp, esp
		push ecx
		push esi
		push edi
		push ebx
		push edx
		mov ecx, dword [ebp + 8]
		cmp ecx, 0x8000000
		jg .ask
		mov esi, dword [ebp + 12]
		mov edi, state
		xor ebx, ebx
		xor edx, edx
		.mainloop:
			lea edx, byte [esi + ebx]
			push edx
			call Isalpha
			test eax, eax
			jne .c
			push edx
			call Isnum
			test eax, eax
			jne .n
			cmp byte [edx], "'"
			je .q
			cmp byte [edx], '"'
			je .q
			push edx
			call Ispunct
			test eax, eax
			jne .d
			cmp byte [edx], ' '
			je .s
			mov byte [edi + ebx], NotCharacter
		.next:
			inc ebx
			loop .mainloop
		mov eax, edi
		.return:
			pop edx
			pop ebx
			pop edi
			pop esi
			pop ecx
			pop ebp
			ret 8
		.c:
			mov byte [edi + ebx], Character
			jmp .next
		.n:
			mov byte [edi + ebx], Number
			jmp .next
		.q:
			mov byte [edi + ebx], Quote
			jmp .next
		.d:
			mov byte [edi + ebx], Delimter
			jmp .next
		.s:
			mov byte [edi + ebx], Space
			jmp .next
		.bfw:
			mov dword [_err], 6 ; 6 = BigFileWarnning
		.err:
			xor eax, eax
			jmp .return
		.ask:
			push _BFW
			push s
			call _printf
			add esp, 8
			.l:
				push c
				push cf
				call _scanf
				add esp, 8
				push _OK
				push s
				call _printf
				add esp, 8
				cmp byte [c], 'y'
				je .mainloop
				cmp byte [c], 'n'
				je .bfw
				push _UN
				push s
				call _printf
				add esp, 8
				jmp .l