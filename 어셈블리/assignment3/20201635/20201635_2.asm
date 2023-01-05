
INCLUDE irvine32.inc


Get_frequencies MACRO addt, addf
	mov ecx, LENGTHOF addt
	dec ecx
	mov esi, OFFSET addt
	mov edi, OFFSET addf
	mov ebx, 4
Loopt:
	movzx eax, BYTE PTR [esi]
	mul ebx
	inc DWORD PTR [edi + eax]
	inc esi
	loop Loopt
ENDM

.data
target BYTE "AAEBDCFBBC",0
freqtable DWORD 256 DUP(0)

.code
main PROC

	Get_frequencies target, freqTable
	mov esi, OFFSET freqtable
	mov ecx, LENGTHOF freqtable
	L1:
	mov eax, [esi]
	call WriteInt
	call Crlf
	add esi, 4
	loop L1

main ENDP
END main