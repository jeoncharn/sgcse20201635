INCLUDE irvine32.inc
;if input nothing, we consider it isn't palindrome

.data
stringinput BYTE 21 DUP(?)
printstring1 BYTE "Is this string palindrome? : ", 0
printstring2 BYTE "It's a palindrome!", 0
printstring3 BYTE "It's NOT a palindrome", 0
divisor DWORD 2
stringlen DWORD ?

.code
main PROC
	mov edx, OFFSET printstring1
	call Writestring
	mov ecx, 21
	mov edx, OFFSET stringinput
	call ReadString
	mov stringlen, eax
	dec stringlen
	mov edx, 0
	div divisor
	mov ecx, eax
	mov eax, stringlen
	mov ebx, 0
Loop1:
	mov dh, [stringinput + ebx]
	mov dl, [stringinput + eax]
	cmp dh, dl
	JNE L1
	inc ebx
	dec eax
	loop Loop1
	mov edx, OFFSET printstring2
	call WriteString
	Jmp L2
L1:
	mov edx, OFFSET printstring3
	call Writestring
L2:
	exit


	exit
main ENDP
END main
	