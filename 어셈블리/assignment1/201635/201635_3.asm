TITLE Task3 code : Exponential Power

INCLUDE irvine32.inc

.data
INCLUDE hw3.inc
save_eax DWORD 0
save_ebx DWORD 0

.code
main PROC
	
	mov eax, X
	mov ebx, Y
Loop_out1:
	cmp ebx, 1
	je EndLoop_out1
	mov edx, eax
	mov ecx, X
Loop_in1:
	cmp ecx, 1
	je EndLoop_in1
	add eax, edx
	dec ecx
	jmp Loop_in1
EndLoop_in1:
	dec ebx
	jmp Loop_out1
EndLoop_out1:
	mov save_eax, eax

	mov eax, Y
	mov ebx, X
Loop_out2:
	cmp ebx, 1
	je EndLoop_out2
	mov edx, eax
	mov ecx, Y
Loop_in2:
	cmp ecx, 1
	je EndLoop_in2
	add eax, edx
	dec ecx
	jmp Loop_in2
EndLoop_in2:
	dec ebx
	jmp Loop_out2
EndLoop_out2:
	mov save_ebx, eax

	mov eax, save_eax
	mov ebx, save_ebx
	call DumpRegs

	INVOKE ExitProcess, 0

main ENDP
END main