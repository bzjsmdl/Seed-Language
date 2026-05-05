Keyword equ 0
Identifer equ 1
Separator equ 2
Data equ 3
NewLine equ 4
section .text
	global _Type
	extern _err, _txt, _idx
	extern _IsKeyword, _IsSep, _IsReg
	extern _Isalpha@4, _Isnum@4, _Ispunct@4
	; int Type(char* type)
	_Type:
		push ebp
		mov ebp, esp
		push esi
		push edi
		push ecx
		push edx
		mov edi, dword [ebp + 8]
		mov esi, _txt
		xor ecx, ecx
		.main:
			cmp ecx, dword [_idx]
			jnl .return

			lea edx, [esi + ecx*4]
			push dword [edx]
			call _IsKeyword
			add esp, 4
			test eax, eax
			jne .k
			
			lea edx, [esi + ecx*4]
			push dword [edx]
			call _Isalpha@4
			test eax, eax
			jne .i

			lea edx, [esi + ecx*4]
			mov eax, dword [edx]
			cmp byte [eax], '_'
			je .i
			cmp byte [eax], '.'
			je .i

			lea edx, [esi + ecx*4]
			push dword [edx]
			call _IsSep
			add esp, 4
			test eax, eax
			jne .s

			lea edx, [esi + ecx*4]
			push dword [edx]
			call _Isnum@4
			test eax, eax
			jne .d


			lea edx, [esi + ecx*4]
			push dword [edx]
			call _IsReg
			add esp, 4
			test eax, eax
			jne .d

			lea edx, [esi + ecx*4]
			mov eax, dword [edx]
			cmp byte [eax], 10
			je .n
			.next:
				inc ecx
				jmp .main
		.return:
			pop edx
			pop ecx
			pop edi
			pop esi
			pop ebp
			ret
		.k:
		   mov byte [edi + ecx], Keyword
		   jmp .next
		.s:
			mov byte [edi + ecx], Separator
			jmp .next
		.i:
			mov byte [edi + ecx], Identifer
		    jmp .next
		.d:
			mov byte [edi + ecx], Data
			jmp .next
		.n:
			mov byte [edi + ecx], NewLine
			jmp .next
