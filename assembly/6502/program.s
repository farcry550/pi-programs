PORTB = $6000
PORTA = $6001
DDRB  = $6002
DDRA  = $6003

E  = %10000000
RW = %01000000
RS = %00100000

  .org $8000

print_char:
  jsr lcd_wait
  sta PORTB
  lda #RS
  sta PORTA
  
  lda #(RS | E)
  sta PORTA

  lda #RS
  sta PORTA

  rts

lcd_instruction:
  jsr lcd_wait
  sta PORTB
  lda #0
  sta PORTA
  lda #E
  sta PORTA
  lda #0
  sta PORTA

  rts

reset:
  lda #%11111111 ; Set all pins on port B to output
  sta DDRB

  lda #%11100000 ; Set top 3 pins on port A to output
  sta DDRA

  lda #%00111000 ; Set 8-bit mode; 2-line display; 5x8 font
  jsr lcd_instruction

  lda #%00001110 ; Display on; Cursor on; Blink off
  jsr lcd_instruction
  
  lda #%00000110 ; Increment and shift cursor; Don't shift display
  jsr lcd_instruction
   
  lda #%00000001 ; Clear display
  jsr lcd_instruction


  ldx #0
print:
  lda message,x
  beq loop
  jsr print_char
  inx
  jmp print

loop:
  jmp loop

message: .asciiz "Swag money 8)"

lcd_wait:
  pha            ; Push value of reg A to stack
  lda #%00000000 ; Port B is input
  sta DDRB       ; Push input setting byte to data direction register B
lcdbusy:
  lda #RW        ; Set the READ flag
  sta PORTA      ; Send the above command
  lda #(RW | E)  ; Set the READ and ENABLE bits
  sta PORTA      ; Send the above command
  lda PORTB      ; Load whatever value is on port B
  and #%10000000 ; Clear out all bits except busy flag
  bne lcdbusy
  
  lda #RW
  sta PORTA
  lda #%11111111 ; Port B is output
  sta DDRB
  pla            ; Pull stored value of A into reg A
  rts

  .org $fffc
  .word reset
  .word $0000
