/* Using ORR to toggle a character case */

   .global _start

_start:
_read:
   MOV R7, #3
   MOV R0, #0
   MOV R2, #1
   LDR R1, =string
   SWI 0

_checkcase:
   LDR R1, =string
   LDR R0, [R1]
   TST R0, #0b00100000 
   BNE _touppercase

_tolowercase:
   ORR R0, R0, #0b00100000
   B _storevalue

_touppercase:
   AND R0, R0, #0b11011111

_storevalue:
   STR R0, [R1]

_write:
   MOV R7, #4
   MOV R0, #1
   MOV R2, #1
   LDR R1, =string
   SWI 0

_exit:
   MOV R7, #1
   SWI 0

.data
string:   .ascii " " 
