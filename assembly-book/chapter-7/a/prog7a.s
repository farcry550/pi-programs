/* How to use Syscall 4 to write a string */

   .global _start
_start:

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
