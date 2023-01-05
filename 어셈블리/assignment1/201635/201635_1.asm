TITLE Task1 code : Summing the Gaps between Array Values

INCLUDE irvine32.inc
.data
INCLUDE hw1.inc

.code
main PROC
	mov ecx, LENGTHOF array1
	dec ecx
	add ecx, ecx
	add ecx, ecx
	mov eax, [array1 + ecx]
	sub eax, [array1]
	call DumpRegs

	INVOKE ExitProcess, 0
main ENDP
END main