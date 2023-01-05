TITLE search a word

INCLUDE irvine32.inc

.data
	printstring1 BYTE "Type_A_String: ", 0
	printstring2 BYTE "A_Word_for_Search: ", 0
	printstring3 BYTE "Found", 0Dh, 0Ah, 0
	printstring4 BYTE "Not found", 0Dh, 0Ah, 0
	printstring5 BYTE "Changed:", 0
	printstring6 BYTE "BYE!", 0Dh, 0Ah, 0
	input_string BYTE 42 DUP(?)
	input_word BYTE 42 DUP(?)
	string_size DWORD 0
	word_size DWORD 0
	teststring BYTE "Test", 0Dh, 0Ah, 0

.code
main PROC

L1:
	mov edx, OFFSET printstring1
	call WriteString
	mov ecx, 42
	mov edx, OFFSET input_string
	call ReadString
	cmp eax, 0
	JE L2
	cmp eax, 40
	JA L1
	mov string_size, eax
	mov edx, OFFSET printstring2
	call WriteString
	mov ecx, 42
	mov edx, OFFSET input_word
	call ReadString
	cmp eax, 0
	JE L2
	mov word_size, eax
	mov eax, 0

Readstr:
	cmp BYTE PTR [input_string + eax], 0
	JE L4
	push eax
	Jmp Compare
Return:
	pop eax
	inc eax
	Jmp Readstr

Compare:
	mov ecx, word_size
	cmp eax, 0
	JE Loopcheck1
	cmp BYTE PTR [input_string + eax], ' '
	JE Loopcheck2
	Jmp Return

Loopcheck1:
	mov bl, BYTE PTR [input_word + ecx - 1]
	cmp [input_string + ecx - 1], bl
	JNE Return
	loop Loopcheck1
	mov ebx, eax
	add ebx, word_size
	cmp [input_string + ebx], ' '
	JE Delete1
	cmp [input_string + ebx], 0
	JE Delete1
	Jmp Return

Delete1:
	mov ebx, word_size
	mov esi, OFFSET input_string
Deleteloop1:
	mov dl, BYTE PTR [input_string + ebx]
	mov BYTE PTR [esi], dl
	cmp dl, 0
	JE L3
	inc ebx
	inc esi
	Jmp Deleteloop1

Loopcheck2:
	mov bl, BYTE PTR [input_word + ecx - 1]
	cmp [input_string + eax + ecx], bl
	JNE Return
	loop Loopcheck2
	mov ebx, eax
	add ebx, word_size
	inc ebx
	cmp [input_string + ebx], ' '
	JE Delete2
	cmp [input_string + ebx], 0
	JE Delete2
	Jmp Return

Delete2:
	mov esi, OFFSET input_string
	add esi, eax
	mov ebx, esi
	add ebx, word_size
	add ebx, 1
DeleteLoop2:
	mov dl, BYTE PTR [ebx]
	mov BYTE PTR [esi], dl
	cmp dl, 0
	JE L3
	inc ebx
	inc esi
	Jmp Deleteloop2

L3:
	mov edx, OFFSET printstring3
	call WriteString
	mov edx, OFFSET printstring5
	call WriteString
	mov edx, OFFSET input_string
	call WriteString
	call Crlf
	Jmp L1
L4:
	mov edx, OFFSET printstring4
	call WriteString
	mov edx, OFFSET printstring5
	call WriteString
	mov edx, OFFSET input_string
	call WriteString
	call Crlf
	Jmp L1

L2:
	mov edx, OFFSET printstring6
	call WriteString
	
	exit

main ENDP
END main