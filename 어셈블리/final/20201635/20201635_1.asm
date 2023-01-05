INCLUDE irvine32.inc

.data
stringinput BYTE "Input : ", 0
star BYTE "*"

.code
main PROC
	mov edx, OFFSET stringinput
	call WriteString
	call ReadInt
	mov ecx, eax
	mov ebx, 1
	mov edx, OFFSET star
Loop1:
	push ecx
	mov ecx, ebx
Loop2:
	mov edx, OFFSET star
	call WriteString
	loop Loop2
	call Crlf
	inc ebx
	pop ecx
	loop Loop1

	exit
main ENDP
END main
	