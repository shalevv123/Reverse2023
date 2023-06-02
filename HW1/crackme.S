	.file	"crackme.c"
	.intel_syntax noprefix
	.text
	.globl	_arg
	.bss
	.align 4
_arg:
	.space 4
	.comm	_mark, 64, 5
	.section .rdata,"dr"
	.section .rdata,"dr"
_divider:
	.long	80
	.text
	.globl	_rand_32
	.def	_rand_32;	.scl	2;	.type	32;	.endef
_rand_32:
	push	ebp
	mov	ebp, esp
	sub	esp, 8
	mov	eax, DWORD PTR [ebp+8]
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR [ebp-4], eax
	mov	eax, DWORD PTR [ebp-4]
	imul	eax, eax, 1103515245
	mov	DWORD PTR [ebp-4], eax
	add	DWORD PTR [ebp-4], 12345
	mov	eax, DWORD PTR [ebp-4]
	shr	eax, 16
	and	eax, 2047
	mov	DWORD PTR [ebp-8], eax
	mov	eax, DWORD PTR [ebp-4]
	imul	eax, eax, 1103515245
	mov	DWORD PTR [ebp-4], eax
	add	DWORD PTR [ebp-4], 12345
	sal	DWORD PTR [ebp-8], 10
	mov	eax, DWORD PTR [ebp-4]
	shr	eax, 16
	and	eax, 1023
	mov	edx, eax
	mov	eax, DWORD PTR [ebp-8]
	xor	eax, edx
	mov	DWORD PTR [ebp-8], eax
	mov	eax, DWORD PTR [ebp-4]
	imul	eax, eax, 1103515245
	mov	DWORD PTR [ebp-4], eax
	add	DWORD PTR [ebp-4], 12345
	sal	DWORD PTR [ebp-8], 10
	mov	eax, DWORD PTR [ebp-4]
	shr	eax, 16
	and	eax, 1023
	mov	edx, eax
	mov	eax, DWORD PTR [ebp-8]
	xor	eax, edx
	mov	DWORD PTR [ebp-8], eax
	mov	eax, DWORD PTR [ebp+8]
	mov	edx, DWORD PTR [ebp-4]
	mov	DWORD PTR [eax], edx
	mov	eax, DWORD PTR [ebp-8]
	leave
	ret
	.section .rdata,"dr"
LC10:
	.ascii "Level 4 Passed!\0"
LC13:
	.ascii "%08X \0"
	.text
	.globl	_printArray
	.def	_printArray;	.scl	2;	.type	32;	.endef
_printArray:
	push	ebp
	mov	ebp, esp
	sub	esp, 12
	mov	eax, DWORD PTR [ebp+12]
	mov	DWORD PTR [ebp-4], eax
	jmp	L24
L27:
	mov	eax, DWORD PTR [ebp-4]
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], OFFSET FLAT:LC13
	call	_printf
	mov	eax, DWORD PTR [ebp-4]
	sub	eax, DWORD PTR [ebp+12]
	sar	eax, 2
	add	eax, 1
	and	eax, 3
	test	eax, eax
	jne	L25
	mov	DWORD PTR [esp], 10
	call	_putchar
	jmp	L26
L25:
	mov	eax, DWORD PTR [ebp-4]
	add	eax, 4
	cmp	DWORD PTR [ebp+16], eax
	ja	L26
	mov	DWORD PTR [esp], 10
	call	_putchar
L26:
	add	DWORD PTR [ebp-4], 4
L24:
	mov	eax, DWORD PTR [ebp-4]
	cmp	eax, DWORD PTR [ebp+16]
	jb	L27
	nop
	nop
	leave
	ret
	.section .rdata,"dr"
LC14:
	.ascii "Level 1 Passed!\0"
	.text
	.globl	_level1
	.def	_level1;	.scl	2;	.type	32;	.endef
_level1:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	cmp	DWORD PTR [ebp+8], 1
	jle	L29
	mov	DWORD PTR [esp], OFFSET FLAT:LC14
	call	_puts
	jmp	L31
L29:
	mov	DWORD PTR [esp], 0
	call	_exit
L31:
	leave
	ret
	.section .rdata,"dr"
LC15:
	.ascii "%d %d\0"
LC16:
	.ascii "%X\0"
LCL0:
	.ascii "%X\n\0"
LC17:
	.ascii "Level 2 Passed!\0"
	.text
	.globl	_level2
	.def	_level2;	.scl	2;	.type	32;	.endef
_level2:
	push	ebp
	mov	ebp, esp
	sub	esp, 64
	mov	DWORD PTR [ebp-46], 1338206604
	mov	DWORD PTR [ebp-42], 1413790233
	mov	BYTE PTR [ebp-38], 44
	mov	DWORD PTR [ebp-4], 0
	jmp	L33
L34:
	lea	eax, [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_rand_32
	cdq
	shr	edx, 24
	add	eax, edx
	movzx	eax, al
	sub	eax, edx
	mov	ecx, eax
	lea	edx, [ebp-37]
	mov	eax, DWORD PTR [ebp-4]
	add	eax, edx
	mov	BYTE PTR [eax], cl
	add	DWORD PTR [ebp-4], 1
L33:
	cmp	DWORD PTR [ebp-4], 8
	jle	L34
	lea	eax, [ebp-28]
	mov	DWORD PTR [esp+8], eax
	lea	eax, [ebp-24]
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], OFFSET FLAT:LC15
	call	_scanf
	mov	eax, DWORD PTR [ebp-24]
	test	eax, eax
	js	L43
	mov	eax, DWORD PTR [ebp-24]
	mov	edx, eax
	lea	eax, [ebp-37]
	add	eax, edx
	and	eax, -4
	mov	DWORD PTR [ebp-16], eax
	mov	eax, DWORD PTR [ebp-28]
	mov	edx, eax
	lea	eax, [ebp-37]
	add	eax, edx
	and	eax, -4
	mov	DWORD PTR [ebp-20], eax
	mov	eax, DWORD PTR [ebp-20]
	mov	DWORD PTR [esp+8], eax
	mov	eax, DWORD PTR [ebp-16]
	mov	DWORD PTR [esp+4], eax
	lea	eax, [ebp-37]
	mov	DWORD PTR [esp], eax
	call	_printArray
	mov	eax, DWORD PTR [ebp-16]
	mov	DWORD PTR [ebp-8], eax
	jmp	L37
L38:
	lea	eax, [ebp-52]
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], OFFSET FLAT:LC16
	call	_scanf
	mov	eax, DWORD PTR [ebp-8]
	mov	eax, DWORD PTR [eax]
	mov	edx, eax
	mov	DWORD PTR [esp+4], edx
	mov	DWORD PTR [esp], OFFSET FLAT:LCL0
	call	_printf
	mov	eax, DWORD PTR [ebp-52]
	xor	eax, edx
	mov	edx, eax
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], OFFSET FLAT:LCL0
	call	_printf
	mov	eax, DWORD PTR [ebp-8]
	mov	DWORD PTR [eax], edx
	add	DWORD PTR [ebp-8], 4
L37:
	mov	eax, DWORD PTR [ebp-8]
	cmp	eax, DWORD PTR [ebp-20]
	jb	L38
	mov	DWORD PTR [ebp-12], 0
	jmp	L39
L41:
	lea	edx, [ebp-37]
	mov	eax, DWORD PTR [ebp-12]
	add	eax, edx
	movzx	edx, BYTE PTR [eax]
	lea	ecx, [ebp-46]
	mov	eax, DWORD PTR [ebp-12]
	add	eax, ecx
	movzx	eax, BYTE PTR [eax]
	cmp	dl, al
	jne	L44
	add	DWORD PTR [ebp-12], 1
L39:
	cmp	DWORD PTR [ebp-12], 8
	jle	L41
	mov	DWORD PTR [esp], OFFSET FLAT:LC17
	call	_puts
	jmp	L32
L43:
	nop
	jmp	L32
L44:
	nop
L32:
	leave
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	# prologue
	push	ebp
	mov	ebp, esp
	sub	esp, 16
	call	___main

	# prepare argument 
	mov	eax, DWORD PTR [ebp+12] # put argv in eax
	add	eax, 4 # point to argv[1]
	mov	eax, DWORD PTR [eax] # put argv[1] in eax
	mov	DWORD PTR [esp], eax # put argv[1] in esp
	call	_atoi # call atoi

	# call level1
	mov	DWORD PTR [ebp-8], eax 
	mov	eax, DWORD PTR [ebp+12]
	mov	DWORD PTR [esp+4], eax
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_level1

	
	# call level2
	mov	eax, DWORD PTR [ebp-8]
	mov	DWORD PTR [esp], eax
	call	_level2


	mov	eax, DWORD PTR [ebp+12]
	mov	eax, DWORD PTR [eax+8]
	mov	DWORD PTR _arg, eax
	mov	eax, DWORD PTR [ebp+12]
	add	eax, 4
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR [esp], eax
	call	_atoi
	mov	DWORD PTR [ebp-8], eax
	lea	eax, [ebp-8]
	mov	DWORD PTR [esp], eax
	call	_rand_32
	cdq
	shr	edx, 24
	add	eax, edx
	movzx	eax, al
	sub	eax, edx
	mov	edx, eax
	mov	eax, edx
	sar	eax, 31
	shr	eax, 27
	add	edx, eax
	and	edx, 31
	sub	edx, eax
	mov	eax, edx
	mov	DWORD PTR _divider, eax
	mov	eax, 0
	leave
	ret
	.ident	"GCC: (MinGW.org GCC Build-2) 9.2.0"
	.def	_exit;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
	.def	_putchar;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_scanf;	.scl	2;	.type	32;	.endef
	.def	_atoi;	.scl	2;	.type	32;	.endef
