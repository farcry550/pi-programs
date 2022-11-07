.data
greeting: .ascii "Hello, "

.text
.global _start

_start:
	ldr r5, greeting_addr
	add r5, #7

	mov r7, #0x3
	mov r0, #0x0
	mov r1, r5
	mov r2, #5
	swi 0

	add r5, #5
	mov r4, #10 
	str r4, [r5]

	mov r7, #0x4
	mov r0, #0x1
	ldr r1, greeting_addr
	mov r2, #13
	swi 0 	
_exit:
	mov r7, #0x1
	mov r0, #55
	swi 0

greeting_addr: .word greeting
