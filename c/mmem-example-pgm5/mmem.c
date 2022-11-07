#include <stdio.h>
#include <sys/mman.h>

int main(void)
{
	int n=5;
	int *ptr = mmap(NULL, n*sizeof(int), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

	if (ptr == MAP_FAILED)
	{
		printf("Mapping Failed\n");
		return 1;
	}

	for (int i=0;i<n; i++)
		ptr[i] = i*10;

	for (int i=0; i<n; i++)
		printf("[%d] ", ptr[i]);

	printf("\n");
	int err = munmap(ptr, 10*sizeof(int));
	if (err != 0)
	{
		printf("Unmapping failed\n");
		return 1;
	}

	return 0;

}
