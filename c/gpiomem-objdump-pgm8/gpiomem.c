#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>

uint32_t* GPIO_BASE;

int main(void)
{
	int fd = open("/dev/gpiomem", O_RDWR | O_SYNC);

	GPIO_BASE = (uint32_t*)mmap(NULL, 0xB4, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

}
