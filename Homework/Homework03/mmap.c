#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

void printElapsedTime(clock_t begin) {
    clock_t end = clock();
    double elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime taken to read file: %f\ns", elapsed_time);
}

// Thank you to https://www.youtube.com/watch?v=m7E9piHcfr4
int main(int argc, char* argv[]) {
    int file = open("text.txt", O_RDONLY, S_IRUSR | S_IWUSR);
    struct stat sb;

    if (fstat(file, &sb) == -1) {
        perror("Could not get file size.\n");
    }
    printf("File size is %lld\n", sb.st_size);
    char* memoryFile = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, file, 0);

    clock_t begin = clock();
    for (int i = 0; i < sb.st_size; i++) {
        printf("%c", memoryFile[i]);
        if (memoryFile[i] == 'X') {
            printf("\n\n*** X MARKS THE SPOT! ***\n");
            close(file);
            printElapsedTime(begin);
            return 0;
        }
    }
    printf("We could not find the buried treasure >:(");
    close(file);
    printElapsedTime(begin);
    return 0;
}
