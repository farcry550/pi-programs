#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

uint32_t* GPIO_BASE;

int main(void)
{
	int fd = open("/dev/gpiomem", O_RDWR | O_SYNC);

	GPIO_BASE = (uint32_t*)mmap(NULL, 0xB4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	if (GPIO_BASE == MAP_FAILED)
	{
		printf("Mapping Failed\n");
		return 1;
	}

	uint32_t FSEL0_07_OUT = 1 << 21;
	*GPIO_BASE = FSEL0_07_OUT;
	
	uint32_t* GPSET0 = GPIO_BASE + (0x1c / sizeof(int));
	uint32_t* GPCLR0 = GPIO_BASE + (0x28 / sizeof(int));

	uint32_t SET_07 = 1 << 7;
	
	while(1)
	{
		*GPSET0 = SET_07;

		sleep(1);		

		printf("ON");

		*GPCLR0 = SET_07;

		sleep(1);

		printf("OFF");
	}

	return 0;

}
