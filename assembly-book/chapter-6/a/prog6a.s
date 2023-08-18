/* Perform R0=R1+R2 */

   .global _start
_start:
   MOV R1, #50     @ Load the value 50 into R1
   MOV R2, #60     @ Load the value 60 into R2
   ADDS R0, R1, R2 @ Add R1 and R2 and store the value in R0

   MOV R7, #1      @ Syscall exit
   SWI 0
