#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
 * Written by Chase Brandenburg
 *
 * Only materials used were base64 and ascii charts provided in "The Secret Life of Programs" by Jonathan E. Steinhart
 *
 */

// Various shifts to move base64 standard codes to ascii
uint8_t ascii_from_base64(uint8_t code) {
  
	if (code <= 25)
  		return code + 65;
 
    	if (code >= 26 && code <= 51)
         	return code + 71;
 
	if (code >= 52 && code <= 61)
		return code - 4;

	if (code == 62)
		return 43;

	if (code == 63)
		return 47;

	if (code == 64)
		return 61;

	return -1;
};


char* convert_to_base64(int size, void* ptr) {
	
	int calc_size = size % 3 == 0 ? size : size + (3 - (size % 3));
	int encoded_str_size = (float)calc_size * 1.334f;

	char* encoded_str  = malloc(encoded_str_size + 1);
	char base64_char;
	
	uint8_t* byte_arr = (uint8_t*)ptr;
	uint8_t byte1;
	uint8_t byte2;
	uint8_t code;
	
	int counted_encoded_bytes = 0;
	int counted_bytes = 0;	

	for (int i = 0; i < calc_size; i+= 3) {

		int remainder = calc_size - size;

		/*
		 * The below line of code starts with our first byte. Let's assume it is the ascii value H, whose decimal value is 72,
		 * or 01001000 in binary. We can represent it as below
		 *
		 * H = 01001000
		 *
		 * For our first byte of base64 encoding, we need the last 6 bits (towards the MSB) 
		 *
		 * H = [010010]00
		 *
		 * To read this value the bits will need to be aligned right. Using the >> operator we can easily accomplish this
		 *
		 * H >> 2 = 00[010010]
		 *
		 * Since shifting right fills in left bits with 0s, we do not need to apply a mask. This leaves us with 
		 * the binary value 00010010, or decimal 18, or S in base64 encoding
		 *
		 */

		code = byte_arr[0] >> 2; // shift bits right 2
		encoded_str[counted_encoded_bytes++] = (char)ascii_from_base64(code);

		/*
		 * The goal of the below 2 lines of code is to move the 6 selected bits into position for reading.
		 * For the second set of 6 bits, 2 bits are taken from the LSB side of byte 1 and 
		 * 4 bits are taken from the MSB side of byte 2. If byte 1 = ascii H and byte 2 = ascii e, our binary
		 * would look like this:
		 *
		 * H = 01001000
		 * e = 01100101
		 *
		 * Or,
		 *
		 * 0100100001100101
		 *
		 * We are only concerned with the rightmost 2 bits of H and the leftmost 4 bits of e.
		 *
		 * H = 010010[00]
		 * e = [0110]0101
		 *
		 * So we need our output to be [00][0110]
		 *
		 * To accomplish this we will need to "or" the bytes together, but to do that the
		 * sets of bits we need have to be positioned correctly. We will do this using shifts and masks.
		 * For the H, we need our 00 to line up in bits 5 and 6. Using the << operator we can easily accomplish this
		 *
		 * H << 4 = 01[00]0000
		 * 
		 * However we still have a 1 left over that is not a part of our desired output. To correct this we can perform
		 * A "mask", where we "and" two values together. Since we only want to read the bits in positions 4 and 5, we can
		 * use a mask as 00110000, which is 0x30 in hex
		 *
		 * 01[00]0000 & 00110000 = 00000000
		 *
		 * For the e our bits are aligned towards the MSB. We need them aligned right, so we can shift them 4
		 *
		 * e >> 4 = 0000[0110]
		 *
		 * Now we have the below combinations
		 *
		 * 00[00]0000
		 * 00 00[0110]
		 *	
		 * We can then "or" these together to get our final value 00000110, which is 3 in decimal, 0x3 in hex, and G in base64 encoding
		 *
		 */

		byte1 = (byte_arr[0] << 4) & 0x30; // shift bits left 4 and mask with 00110000
		byte2 = byte_arr[1] >> 4; // shift bits right 4
		code = byte1 | byte2; // or the values together
		encoded_str[counted_encoded_bytes++] = (char)ascii_from_base64(code);

		if (i == calc_size - 3 && remainder == 2) // if we need padding...
			code = 0x40; // set the code to be an =
		else {
			byte1 = (byte_arr[1] << 2) & 0x3c; // shift bits left 2 and mask with 00111100
			byte2 = byte_arr[2] >> 6; // shift bits right 6
			code = byte1 | byte2; // or the values together
		}

		encoded_str[counted_encoded_bytes++] = (char)ascii_from_base64(code);

		if (i == calc_size - 3 && (remainder == 1 || remainder == 2)) // if we need padding...
			code = 0x40; // set the code to be an =
		else 
			code = byte_arr[2] & 0x3f; // only take the last 6 bits by masking with 00111111

		encoded_str[counted_encoded_bytes++] = (char)ascii_from_base64(code);

		counted_bytes += 3; // increment counted bytes
		
		if (counted_bytes < size)
			byte_arr = &byte_arr[3]; // shift our pointer past the 3 bytes we just encoded

	}

	encoded_str[counted_encoded_bytes + 1] = 0x0; // append a null terminating character

	return encoded_str;
}

int main(int argc, char *argv[]) {

	int size = 0;
	uint8_t *ptr = argv[1];

	while (*ptr != 0x0) {
		size++;
		ptr++;
	}

	char* encoded_str = convert_to_base64(size, argv[1]);
	int count;

	while (encoded_str[count] != 0x0) {
		printf("%c", encoded_str[count]);
		count++;
	}

	printf("\n");

	return 0;
}
