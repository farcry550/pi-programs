.data
var1: .word 1

.text
.global _start

_start:

_load_chars:
	ldr r0, adr1
	mov r1, #72
	str r1, [r0]
	mov r1, #69
	str r1, [r0 , #1]
	mov r1, #76
	str r1, [r0 , #2]
	mov r1, #76
	str r1, [r0 , #3]
	mov r1, #79
	str r1, [r0 , #4]
	mov r1, #32
	str r1, [r0 , #5]
	mov r1, #87
	str r1, [r0 , #6]
	mov r1, #79
	str r1, [r0 , #7]
	mov r1, #82
	str r1, [r0 , #8]
	mov r1, #76
	str r1, [r0 , #9]
	mov r1, #68
	str r1, [r0 , #10]
	mov r1, #33
	str r1, [r0 , #11]
	mov r1, #10
	str r1, [r0 , #12]	
_print_chars:
	mov r7, #0x4
	mov r0, #0x1
	ldr r1, adr1
	mov r2, #0xD
	swi 0
_exit:
	mov r7, #0x1
	mov r0, #0x1
	swi 0

adr1: .word var1 
