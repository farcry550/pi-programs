#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define ROM_SIZE 32768

unsigned 
int main(void) {

    uint8_t rom[ROM_SIZE];
    uint8_t* ptr = rom;
    
    for (int i = 0; i < ROM_SIZE; i++) {
        ptr[i] = 0xea;
    }

    rom[0] = 0xa9; // lda #$ff
    rom[1] = 0xff;

    rom[2] = 0x8d; // sta $6002
    rom[3] = 0x02;
    rom[4] = 0x60;

    rom[5] = 0xa9; // lda #$55
    rom[6] = 0x55;

    rom[7] = 0x8d; // sta $6000
    rom[8] = 0x00;
    rom[9] = 0x60;

    rom[10] = 0xa9; // lda #$aa
    rom[11] = 0xaa;

    rom[12] = 0x8d; // sta $6000
    rom[13] = 0x00;
    rom[14] = 0x60;

    rom[15] = 0x4c; // jmp $8005
    rom[16] = 0x05;
    rom[17] = 0x80;

    rom[0x7ffc] = 0x00;
    rom[0x7ffd] = 0x80;

    FILE *write_ptr;

    write_ptr = fopen("rom.bin","wb");  // w for write, b for binary

    fwrite(rom,sizeof(rom),1,write_ptr); // write 10 bytes from our bu
}
