/* Signed division */

   .global _start
_start:

   MOV R3, #20     @ Numerator
   MOV R4, #5      @ Denominator
   SDIV R0, R3, R4 @ R0=R3/R4

   MOV R7, #1
   SWI 0

