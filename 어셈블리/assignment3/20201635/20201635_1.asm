Title: sorting problem

INCLUDE irvine32.inc
INCLUDE hw3.inc

.data
	printstring1 BYTE "Before sort : ", 0
	printstring2 BYTE "After sort : ", 0
	printstring3 BYTE "Bye!", 0
	sortcount1 DWORD ?
	sortcount2 DWORD ?
	savex1 DWORD ?
	savey1 DWORD ?
	savex2 DWORD ?
	savey2 DWORD ?
	comma BYTE ", ", 0
	printtest BYTE "execute?", 0

.code
main PROC
	;print before sort
	mov edx, OFFSET printstring1
	call WriteString
	mov ecx, LenData
	mov esi, OFFSET ArrData
	mov eax, DWORD PTR [esi]
	call WriteHex
	dec ecx
printloop1:
	mov edx, OFFSET comma
	call WriteString
	add esi, 4
	mov eax, DWORD PTR [esi]
	call WriteHex

	loop printloop1
	call Crlf

	;sorting 
	mov edx, 0
	mov eax, LenData
	mov sortcount2, eax
	mov ebx, 2   ;divisor
	div ebx      ; eax will save quotient
	mov sortcount1, eax
	sub sortcount2, eax
	mov ebx, 10000h ; divisor

Loopout1:
	mov esi, OFFSET ArrData
	add esi, 4 ; pointing 2nd index
	dec sortcount1
	cmp sortcount1, 0
	jle Loopendout1     ; consider LenData is 0
	mov ecx, sortcount1
Loopin1:
	mov edx, 0
	mov eax, DWORD PTR [esi]
	div ebx
	mov savex1, eax
	mov savey1, edx
	
	mov edx, 0
	mov eax, DWORD PTR [esi + 8]
	div ebx

.IF savex1 > eax
	jmp Loopendin1
.ELSEIF savex1 == eax && savey1 < edx
	jmp Loopendin1
.ENDIF
	call Exchange
Loopendin1:
	add esi, 8
	loop Loopin1
	jmp Loopout1
Loopendout1:

Loopout2:
	mov esi, OFFSET ArrData
	dec sortcount2
	cmp sortcount2, 0
	jle Loopendout2     ; consider LenData is 0
	mov ecx, sortcount2
Loopin2:
	mov edx, 0
	mov eax, DWORD PTR [esi]
	div ebx
	mov savex1, eax
	mov savey1, edx
	
	mov edx, 0
	mov eax, DWORD PTR [esi + 8]
	div ebx

.IF savex1 < eax
	jmp Loopendin2
.ELSEIF savex1 == eax && savey1 > edx
	jmp Loopendin2
.ENDIF
	call Exchange
Loopendin2:
	add esi, 8
	loop Loopin2
	jmp Loopout2
Loopendout2:

	;print changed array
	mov edx, OFFSET printstring2
	call WriteString
	mov ecx, LenData
	mov esi, OFFSET ArrData
	mov eax, DWORD PTR [esi]
	call WriteHex
	dec ecx
printloop2:
	mov edx, OFFSET comma
	call WriteString
	add esi, 4
	mov eax, DWORD PTR [esi]
	call WriteHex

	loop printloop2
	call Crlf

	mov edx, OFFSET printstring3
	call WriteString
	call Crlf
main ENDP

Exchange PROC
	;change [esi] value and [esi + 8] value
	mov eax, DWORD PTR [esi]
	mov edx, DWORD PTR [esi + 8]
	mov DWORD PTR [esi], edx
	mov DWORD PTR [esi + 8], eax
	ret
Exchange ENDP

END main