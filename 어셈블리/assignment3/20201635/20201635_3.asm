INCLUDE irvine32.inc

.data
	printmenu BYTE "1. x AND y", 0dh, 0ah,
				"2. x OR y", 0dh, 0ah,
				"3. NOT x", 0dh, 0ah,
				"4. x XOR y", 0dh, 0ah,
				"5. Exit program", 0dh, 0ah, 0
	printx BYTE "Enter x : ", 0
	printy BYTE "Enter y : ", 0
	print1 BYTE "Result of x AND y : ", 0
	print2 BYTE "Result of x OR y : ", 0
	print3 BYTE "Result of NOT : ", 0
	print4 BYTE "Result of x XOR y : ", 0
	printchoose BYTE "Choose Calculation Mode : ", 0
	printchange BYTE "Do you want to change the mode(Y/N)? : ", 0
	printend BYTE "Bye!", 0
	saveyn BYTE 2 DUP(?)

	CaseTable DWORD 1
	DWORD AND_op
	EntrySize = ($ - CaseTable)
	DWORD 2
	DWORD OR_op
	DWORD 3
	DWORD NOT_op
	DWORD 4
	DWORD XOR_op

.code
main PROC
L1:
	mov edx, OFFSET printmenu
	call WriteString
	call Crlf
L2:
	mov edx, OFFSET printchoose
	call WriteString
	call ReadHex
	.IF eax < 1 || eax > 5
		jmp L2
	.ELSEIF eax==5
		call Crlf
		mov edx, OFFSET printend
		call WriteString
		call Crlf
		exit
	.ENDIF
	mov ebx, OFFSET CaseTable
	mov ecx, 4
Loop1:
	cmp eax, [ebx]
	JE Lcall
	add ebx, EntrySize
	loop Loop1 

Lcall:
	push ebx     ; some procedures use ebx
	call NEAR PTR [ebx + 4]
	call Crlf
	pop ebx
L3:
	mov edx, OFFSET printchange
	call WriteString
	mov edx, OFFSET saveyn
	mov ecx, 2
	call ReadString
	mov al, [saveyn]
	.IF al=='Y' || al=='y'
		call Crlf
		Jmp L1
	.ELSEIF al=='N' || al=='n'
		call Crlf
		Jmp Lcall
	.ELSE
		Jmp L3
	.ENDIF


main ENDP

AND_op PROC
	;use eax and ebx to calculate
	mov edx, OFFSET printx
	call WriteString
	call ReadHex
	mov ebx, eax
	mov edx, OFFSET printy
	call WriteString
	call ReadHex
	mov edx, OFFSET print1
	call WriteString
	AND eax, ebx
	call WriteHex
	call Crlf

	ret
AND_op ENDP

OR_op PROC
	;use eax and ebx to calculate
	mov edx, OFFSET printx
	call WriteString
	call ReadHex
	mov ebx, eax
	mov edx, OFFSET printy
	call WriteString
	call ReadHex
	mov edx, OFFSET print2
	call WriteString
	OR eax, ebx
	call WriteHex
	call Crlf

	ret
OR_op ENDP

NOT_op PROC
	;use eax to calculate
	mov edx, OFFSET printx
	call WriteString
	call ReadHex
	mov edx, OFFSET print3
	call WriteString
	NOT eax
	call WriteHex
	call Crlf

	ret
NOT_op ENDP

XOR_op PROC
	;use eax and ebx to calculate
	mov edx, OFFSET printx
	call WriteString
	call ReadHex
	mov ebx, eax
	mov edx, OFFSET printy
	call WriteString
	call ReadHex
	mov edx, OFFSET print4
	call WriteString
	XOR eax, ebx
	call WriteHex
	call Crlf

	ret
XOR_op ENDP

END main