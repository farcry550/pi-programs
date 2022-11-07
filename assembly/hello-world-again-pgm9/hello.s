.data
msg:	.ascii "Hello, world!\n"

.text

.global _start
_start:

	mov r7, #0x4
	mov r0, #0x1
	ldr r1, =msg
	mov r2, #14
	swi 0

	mov r7, #0x1
	mov r0, #0x0
	swi 0
