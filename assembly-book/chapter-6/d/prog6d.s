/* Multiply two numbers with accumulate R0=(R1*R2)+R3 */

   .global _start
_start:
   MOV R1, #20
   MOV R2, #5
   MOV R3, #10
   MLA R0, R1, R2, R3 @ R0=(R1*R2)+R3

   MOV R7, #1
   SWI 0
