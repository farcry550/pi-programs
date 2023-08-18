.data
msg:  .ascii "          "
file: .asciz "input.txt"

.text
_print:
  mov r7, #0x4
  mov r0, #0x1
  ldr r1, =msg
  mov r2, #0xa
  swi 0
  bx lr

_atoi:
  

.global _start
_start:
  @mov r7, #0x4
  @mov r0, #0x1
  @ldr r1, =msg
  @mov r2, #0xe
  @swi 0

  @ Open the file
  mov r7, #0x5
  ldr r0, =file
  mov r1, #0x0
  swi 0

  @ Read the contents
  mov r7, #0x3
  ldr r1, =msg
  mov r2, #0xa
  swi 0
  
  @ Call print
  bl _print

  mov r7, #0x1
  mov r0, #0x5
  swi 0
