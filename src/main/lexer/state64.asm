section .data
	s db "%s"
	cf db " %c"
	c db 0
	Character equ 0
	Delimter equ 1
	Quote equ 2
	Number equ 3
	NotCharacter equ 4
	Space equ 5
section .bss
	stateArr resb 0x4000000
section .text
	global state
	extern Isalpha, Isnum, Ispunct
	extern scanf, printf
	extern err, OK, BFW, UN
	; char* state(unsigned long long int length, char* text)
	state:
		push rsi
		push rdi
		push rbx
		cmp rcx, 0x4000000
		jg .bfw
		mov rsi, rdx
		mov rdi, stateArr
		xor rbx, rbx
		xor rdx, rdx
		.mainloop:
			lea rdx, byte [rsi + rbx]
            push rcx
			mov rcx, rdx
			call Isalpha
			test rax, rax
			jne .c
			mov rcx, rdx
			call Isnum
			test rax, rax
			jne .n
			cmp byte [rdx], "'"
			je .q
			cmp byte [rdx], '"'
			je .q
			mov rcx, rdx
			call Ispunct
			test rax, rax
			jne .d
			cmp byte [rdx], ' '
			je .s
			mov byte [rdi + rbx], NotCharacter
		.next:
            pop rcx
			inc rbx
			loop .mainloop
		mov rax, rdi
		.return:
			pop rbx
			pop rdi
			pop rsi
			ret
		.c:
			mov byte [rdi + rbx], Character
			jmp .next
		.n:
			mov byte [rdi + rbx], Number
			jmp .next
		.q:
			mov byte [rdi + rbx], Quote
			jmp .next
		.d:
			mov byte [rdi + rbx], Delimter
			jmp .next
		.s:
			mov byte [rdi + rbx], Space
			jmp .next
		.bfw:
			mov dword [err], 6 ; 6 = BigFileWarnning
		.err:
			xor rax, rax
			jmp .return
