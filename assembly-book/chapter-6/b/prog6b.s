/* Add two 64-bit numbers together */

   .global _start
_start:

   MOV R2, #0xFFFFFFFF
   MOV R3, #0x1
   MOV R4, #0xFFFFFFFF
   MOV R5, #0xFF
   ADDS R0, R2, R4
   ADCS R1, R3, R5

   MOV R7, #1
   SWI 0

