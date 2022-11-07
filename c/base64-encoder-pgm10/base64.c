#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define bytes_1_4_mask 0x3f
#define bytes_2_3_mask 0x30
 
       
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

	char* encoded_str = malloc(encoded_str_size + 1);

	uint8_t* byte_arr = (uint8_t*)ptr;

	uint8_t byte1;
	uint8_t byte2;
	uint8_t code;

	char base64_char;
	
	int counted_encoded_bytes = 0;
	int counted_bytes = 0;	
	

	for (int i = 0; i < calc_size; i += 3) {
		int remainder = calc_size - size;

		code = (byte_arr[0] >> 2) & 0x3f;
		encoded_str[counted_encoded_bytes++] = (char)ascii_from_base64(code);

		byte1 = (byte_arr[0] << 4) & 0x30;
		byte2 = byte_arr[1] >> 4;
		code = byte1 | byte2;
		encoded_str[counted_encoded_bytes++] = (char)ascii_from_base64(code);

		byte1 = (byte_arr[1] << 2) & 0x3c;
		byte2 = (byte_arr[2] >> 6) & 0x3;
		code = byte1 | byte2;

		if (i == calc_size - 3 && remainder == 2)
			code = 0x40;

		encoded_str[counted_encoded_bytes++] = (char)ascii_from_base64(code);

		code = byte_arr[2] & 0x3f;

		if (i == calc_size - 3 && (remainder == 1 || remainder == 2))
			code = 0x40;
	
		encoded_str[counted_encoded_bytes++] = (char)ascii_from_base64(code);

		counted_bytes += 3;

		if (counted_bytes < size)
			byte_arr = &byte_arr[3];

	}

	encoded_str[counted_encoded_bytes + 1] = 0x0;

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

	//convert_to_base642(size, msg);

	//char* output = convert_to_base64(size, msg);
	
	//printf("%d\n", sizeof(msg) * sizeof(char));

	return 0;
}
