#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getIndex(char ch, char old[]) {
    for (int i = 0; i < strlen(old); i++) {
        if (old[i] == ch) {
            return i;
        }
    }
    return -1;
}

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-t") == 0) {
        FILE *fptr = fopen(argv[4], "r");
        FILE *output = fopen("output.txt", "w");
        char old[20];
        strcpy(old, argv[2]);
        char new[20];
        strcpy(new, argv[3]);
        char ch;

        while ((ch = fgetc(fptr)) != EOF) {
            if (getIndex(ch, old) >= 0) {
                fprintf(output, "%c", new[getIndex(ch, old)]);
            } else { 
                fprintf(output, "%c", ch);
            }     
        }
    } else if (strcmp(argv[1], "-d") == 0) {
        FILE *fptr = fopen(argv[3], "r");
        FILE *output = fopen("output.txt", "w");
        char old[20];
        strcpy(old, argv[2]);
        char ch;

        while (fscanf(fptr, "%c", &ch) != EOF) {
            if (getIndex(ch, old) >= 0) {
                continue;
            } else {
                fprintf(output, "%c", ch);   
            }
        }
    } else if (strcmp(argv[1], "-s") == 0) {

    } else if (strcmp(argv[1], "-c") == 0) {

    } else { // has no option

    }
    return 0;
}