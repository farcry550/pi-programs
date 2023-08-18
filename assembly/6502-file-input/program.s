PORTB = $6000
PORTA = $6001
DDRB  = $6002
DDRA  = $6003

E  = %10000000
RW = %01000000
RS = %00100000

  .org $8000

print_char:
  lda #RS
  sta PORTA
  
  lda #(RS | E)
  sta PORTA

  lda #RS
  sta PORTA

  rts

reset:
  lda #%11111111 ; Set all pins on port B to output
  sta DDRB

  lda #%11100000 ; Set top 3 pins on port A to output
  sta DDRA

  lda #%00111000 ; Set 8-bit mode; 2-line display; 5x8 font
  sta PORTB

  lda #0         ; Clear RS/RW/E bits
  sta PORTA
  lda #E         ; Set E high
  sta PORTA
  lda #0         ; Clear RS/RW/E bits
  sta PORTA

  lda #%00001110 ; Display on; Cursor on; Blink off
  sta PORTB

  lda #0
  sta PORTA
  lda #E
  sta PORTA
  lda #0
  sta PORTA
  
  lda #%00000110 ; Increment and shift cursor; Don't shift display
  sta PORTB

  lda #0
  sta PORTA
  lda #E
  sta PORTA
  lda #0
  sta PORTA
   
  lda #%00000001 ; Clear display
  sta PORTB

  lda #0
  sta PORTA
  lda #E
  sta PORTA
  lda #0
  sta PORTA

  

loop:
  jmp loop

  .org $fffc
  .word reset
  .word $0000

file:
  .org $9000
  .binary "input.txt"
