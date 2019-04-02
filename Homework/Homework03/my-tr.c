#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    FILE *fptr = fopen(argv[3], "r");
    if (fptr == NULL) {
        printf("Cannot open file.\n");
        exit(0);
    }
    char c = fgetc(fptr);
    while (c != EOF) {
        if (c >= 97 && c <= 122) {
            c -= 32;
        }
        printf("%c", c);
        c = fgetc(fptr);
    }
    fclose(fptr);
    return 0;
}