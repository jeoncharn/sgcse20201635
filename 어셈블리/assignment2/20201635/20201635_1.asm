INCLUDE irvine32.inc

.data
val1 BYTE "65", 0
savesum DWORD 0
mulnum DWORD 7

.code
main PROC
	mov eax, 1
	mov ecx, LENGTHOF val1
	dec ecx
	mov esi, OFFSET val1
	
L1:
	movzx ebx, BYTE PTR [esi + ecx - 1]
	sub ebx, 48
	push eax
	mul ebx
	add savesum, eax
	pop eax
	mul mulnum
	loop L1
	
	mov eax, savesum
	call DumpRegs
	exit
main ENDP
END main
