#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please input a single argument of the desired length of the array.");
        return 0;
    }
    int length = strtol(argv[1], NULL, 10);
    if (length < 0) {
        printf("Please input a positive interger.");
        return 0;
    }
    int nums[length];
    srand(time(0));
    for (int i = 0; i < length; i++) {
        nums[i] = (rand() % 100) + 1;
    }
    int ithElement = 57;
    printf("Here is every 4096th element in the array:\n");
    printf("------------------------------------------\n");
    for (int i = 0; i < length; i++) {
        int iPlusOne = i + 1;
        if ((i + 1) % ithElement == 0) {
            printf("%d\n", nums[i]);
        }
    }
    return 0;
}