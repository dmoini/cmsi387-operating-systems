#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int main(int argc, char* argv[]) {
    clock_t begin = clock();
    if (1 == argc) {
        printf("Please enter one argument, the array size.\n");
        exit(0);
    }
    int length = atoi(argv[1]) ;
    printf("Using array of %d elements.", length);
    int* vmArray = (int* ) malloc(sizeof(int) * length);
    if (NULL == vmArray) {
        printf("Could not allocate array of %d size.\n", length);
        exit(-1);
    }
    srand(time(0));
    for (int i = 0; i < length; i++) {
        vmArray[i] = (rand() % 100);
        if (i % 4096 == 0) {
            printf("Array element %d is %d\n", i, vmArray[i]);
        }
    }
    free(vmArray);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Execution time: %fs\n", time_spent);
    return 0;
}