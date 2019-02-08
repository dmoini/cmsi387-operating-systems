#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct KeyValue {
  char *key;
  int value;
};

int main(int argc, char **argv) {
  int quantum = 40;
  struct KeyValue arr[argc];
  size_t n = sizeof(arr) / sizeof(arr[0]);
  int counter = 0;
  for (int i = 1; i < argc - 1; i += 2) {
    arr[counter].key = argv[i];
    arr[counter].value = atoi(argv[i + 1]);
    // printf("%s : %d\n", arr[i].key, arr[i].value);
    counter++;
  }

  printf("%zu\n", n);
  int limit = n / 2;
  while (limit > 0) {
    for (int j = 0; j < argc - 1; j += 1) {
      arr[j].value -= quantum;
      if (arr[j].value - quantum <= 0) {
        arr[j].value = 0;
        limit--;
      }
      //   printf("%d", counter);
      printf("%s : %i  : %i\n", arr[j].key, quantum, arr[j].value);
    }
  }
  return 0;
}