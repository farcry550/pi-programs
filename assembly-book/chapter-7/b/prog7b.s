/* How to use Syscall 3 to read from keyboard */

   .global _start
_start:
_read:

   MOV R7, #3
   MOV R0, #0
   MOV R2, #5
   LDR R1, =string
   SWI 0

_write:

   MOV R7, #4
   MOV R0, #1
   MOV R2, #19
   LDR R1, =string
   SWI 0

_exit:

   MOV R7, #1
   SWI 0

.data
string: .ascii "Hello World String\n"
