#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int main(int argc, char* argv[]) {
    if (1 == argc) {
        printf("Please enter one argument, the array size.\n");
        exit(0);
    }
    int length = atoi(argv[1]) ;
    printf("Using array of %d elements.\n", length);
    int* vmArray = (int*) malloc(sizeof(int) * length);
    if (NULL == vmArray) {
        printf("Could not allocate array of %d size.\n", length);
        exit(-1);
    }
    srand(time(0));
    for (int i = 0; i < length; i++) {
        vmArray[i] = (rand() % 100);
    }

    int averageTimesLength = (length / 4096) + 1;
    double averageTimes[averageTimesLength];

    for (int i = 0; i < length; i += 4096) {
        clock_t begin = clock();
        vmArray[i];
        // printf("Array element %d is %d\n", i, vmArray[i]);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

        averageTimes[i / 4096] = time_spent;
    }    

    double sum = 0.0;
    for (int i = 0; i < averageTimesLength; i++) {
        // printf("Access time: %fs\n", averageTimes[i]);
        sum += averageTimes[i];
    }

    double averageTime = sum / (double) averageTimesLength;
    printf("Average Access time: %fs\n", averageTime);

    free(vmArray);
    return 0;
}