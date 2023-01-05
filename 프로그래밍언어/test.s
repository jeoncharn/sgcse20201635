	.file	"test.c" // file 이름이 test.c인 것을 파악할 수 있다.
	.comm	a,4000,32 // a에 4000 byte를 할당 받는다.
	.comm	aa,12,8 // aa에 12 byte를 할당 받는다.
	.comm	d1,4,4 // d1에 4 byte를 할당 받는다.
	.comm	bb,4,4 // bb에 4 byte를 할당 받는다.
	.comm	cc,8,8 // cc에 4 byte를 할당 받는다.
	.comm	k,4,4 // k에 4 byte를 할당 받는다.
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp 
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	a+1828(%rip), %eax // row major order에 의해 +1828이 된다.
	movl	%eax, k(%rip) // k에 값을 저장한다.
	movl	$0, d1(%rip) // Sun을 의미하는 0을 d1에 저장한다.
	movl	k(%rip), %eax 
	movl	%eax, bb(%rip) // k 값을 bb에 저장한다.
	movq	$bb, cc(%rip) // bb의 주소를 cc에 저장한다.
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
