TITLE Task4 code : Copy a String in Reverse Order

INCLUDE irvine32.inc

.data
INCLUDE hw4.inc

.code
main PROC
	mov eax, SIZEOF source
	mov ebx, OFFSET target
	mov ch, [source + eax - 1]
	mov [ebx + eax - 1], ch


Loop1:
	cmp eax, 1
	je EndLoop1
	mov ch, [source + eax - 2]
	mov [ebx], ch
	dec eax
	inc ebx
	jmp Loop1
EndLoop1:
	mov edx, OFFSET target
	call WriteString

	INVOKE ExitProcess, 0

main ENDP
END main