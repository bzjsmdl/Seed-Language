Keyword equ 0
Identifer equ 1
Separator equ 2
Data equ 3
NewLine equ 4
section .text
	global Type
	extern err, txt, idx
	extern malloc, IsKeyword, IsSep, IsReg
	extern Isalpha, Isnum, Ispunct
	Type:
		push rsi
		push rdi
        push rdx
		mov rdi, rcx
		mov rsi, txt
		xor rcx, rcx
		.main:
			cmp rcx, qword [idx]
			jnl .return

			lea rdx, [rsi + rcx*8]
			push rcx
			sub rsp, 32
            mov rcx, qword [rdx]
			call IsKeyword
			add rsp, 32
			pop rcx
			test rax, rax
			jne .k

			lea rdx, [rsi + rcx*8]
			push rcx
			sub rsp, 32
            mov rcx, qword [rdx]
			call Isalpha
			add rsp, 32
            pop rcx
			test rax, rax
			jne .i

			lea rdx, [rsi + rcx*8]
			mov rax, qword [rdx]
			mov al, byte [rax]
			cmp al, '_'
			je .i
			cmp al, '.'
			je .i

			push rcx
			sub rsp, 32
            mov rcx, qword [rdx]
			call IsSep
			add rsp, 32
			pop rcx
			test rax, rax
			jne .s

			lea rdx, [rsi + rcx*8]
			push rcx
			sub rsp, 32
			mov rcx, qword [rdx]
			call Isnum
			add rsp, 32
			pop rcx
			test rax, rax
			jne .d

			lea rdx, [rsi + rcx*8]
			push rcx
			sub rsp, 32
			mov rcx, qword [rdx]
			call IsReg
			add rsp, 32
			pop rcx
			test rax, rax
			jne .d

			lea rdx, [rsi + rcx*8]
            mov rax, qword [rdx]
			cmp byte [rax], 10
			je .n
			.next:
				inc rcx
				jmp .main
		.return:
			pop rdx
			pop rdi
			pop rsi
			ret
		.k:
		   mov byte [rdi + rcx], Keyword
		   jmp .next
		.s:
			mov byte [rdi + rcx], Separator
			jmp .next
		.i:
			mov byte [rdi + rcx], Identifer
		    jmp .next
		.d:
			mov byte [rdi + rcx], Data
			jmp .next
        .n:
			mov byte [rdi + rcx], NewLine
			jmp .next
