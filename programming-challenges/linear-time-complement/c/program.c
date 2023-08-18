#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE* fp;
  char* line = NULL;
  size_t len = 0;
  size_t read;

  int nums[100];
  int* ptr = nums;

  for (int i = 0; i < 100; i++)
    nums[i] = -1;

  int target = atoi(argv[1]);

  fp = fopen("../input.txt", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  int index = 0;

  while((read = getline(&line, &len, fp)) != -1) {
    int num = atoi(line);
    int complement = target - num;
    
    if (complement > -1) {
	nums[num] = num;

	if (nums[complement] != -1) {
          printf("%d, %d\n", index, complement);
 	  printf("%d, %d\n\n", num, complement);
	}
    }

    index++;
  }

  return 0;
}
