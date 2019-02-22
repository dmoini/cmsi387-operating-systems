
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  int* array;
  int arraySize = atoi(argv[1]);
  array = malloc(sizeof(int) * arraySize);
  int i;
  srand(23);
  for (i = 0; i < arraySize; i++) {
    array[i] = rand() % 100;
    if (i % 4096 == 0) {
      printf("%d\n", array[i]);
    }
  }
  free(array);
  return 0;
}