#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  char name[20];
  printf("Enter a name: ");
  fgets(name, 20, stdin);
  printf("\n\n   Hello, %s", name);
  return 0;
}
