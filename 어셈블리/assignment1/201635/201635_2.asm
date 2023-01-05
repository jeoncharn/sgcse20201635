TITLE Task2 code : Fibonacci Numbers

INCLUDE irvine32.inc
.data
INCLUDE hw2.inc
n_1num DWORD 1
n_2num DWORD 1

.code
main PROC

mov ecx, fib
Loop1:
	cmp ecx, 2
	je EndLoop1
	mov eax, n_1num
	mov ebx, n_2num
	add n_1num, ebx
	mov n_2num, eax
	dec ecx
	jmp Loop1
EndLoop1:
	mov eax, n_1num
	call DumpRegs


	INVOKE ExitProcess, 0
main ENDP
END main