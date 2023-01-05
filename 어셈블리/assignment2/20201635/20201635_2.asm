INCLUDE irvine32.inc

.data
printstring1 BYTE "Enter a Multiplier : ", 0
printstring2 BYTE "Enter a Multiplicand : ", 0
printstring3 BYTE "Produce : ", 0
printstring4 BYTE "Bye!", 0
savesum DWORD 0

.code
main PROC
L1:
	mov edx, OFFSET printstring1
	call WriteString
	call ReadHex
	jc L2
	mov ebx, eax
	mov edx, OFFSET printstring2
	call WriteString
	call ReadHex
	JC L2
	mov edx, OFFSET printstring3
	call WriteString

	mov ecx, 32
L3:
	shr eax, 1
	jnc L4
	add savesum, ebx
L4:
	add ebx, ebx
	loop L3

	mov eax, savesum
	call WriteHex
	mov savesum, 0
	call Crlf
	jmp L1
L2:
	mov edx, OFFSET printstring4
	call WriteString
	exit
main ENDP
END main