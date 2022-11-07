#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
	int *ptr = malloc(sizeof(int) * 3);	
	
	*ptr = 2;
	
	*ptr |= 1;

	printf("%d\n", *ptr);

	return 0;
}
