/* Convert number to binary for printing */

   .global _start

_start:
   MOV R6, #0xFCFC
   MOV R10, #1
   MOV R9, R10, LSL #31
   LDR R1, =string

_bits:
   TST R6, R9
   BEQ _print0
   MOV R8, R6
   MOV R0, #49
   STR R0, [R1]
   BL _write
   MOV R6, R8
   BAL _noprint1

_print0:
   MOV R8, R6
   MOV R0, #48
   STR R0, [R1]
   BL _write
   MOV R6, R8

_noprint1:
   MOVS R9, R9, LSR #1
   BNE _bits

_exit:
   MOV R7, #1
   SWI 0

_write:
   MOV R0, #1
   MOV R2, #1
   MOV R7, #4
   SWI 0
   MOV PC, LR

.data
string:   .ascii " "
