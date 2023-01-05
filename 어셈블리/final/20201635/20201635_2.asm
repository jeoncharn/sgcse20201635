INCLUDE irvine32.inc

.data
stringinput BYTE 42 DUP(?)
printstring1 BYTE "Type_A_String_To_Reverse: ", 0
printstring2 BYTE "Reversed_String: ", 0
printstring3 BYTE "Bye!", 0

.code
main PROC
L1:
	mov edx, OFFSET printstring1
	call Writestring
	mov ecx, 42
	mov edx, OFFSET stringinput
	call ReadString
	cmp eax, 40
	JA L1
	cmp eax, 0
	JE End1
	mov edx, OFFSET printstring2
	call WriteString

	mov ecx, eax
Loop1:
	mov al, [stringinput + ecx - 1]
	call WriteChar
	loop Loop1
	call Crlf
	Jmp L1

End1:
	mov edx, OFFSET printstring3
	call WriteString

	exit
main ENDP
END main
	