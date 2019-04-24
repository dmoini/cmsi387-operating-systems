#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define NEWLINE() printf("\n");
#define DIVIDER() printf("===========================================================================================\n");

int const MAX_PROCESSES = 20;
int const BUFFER_SIZE = 1024;

struct Hog {
    int PID;
    double CPU;
    double MEM;
    // char COMMAND[1021];  // may delete, idk
};

void printHog(struct Hog h) {
    printf("PID: %d     %%CPU: %.1f     %%MEM: %.1f\n", h.PID, h.CPU, h.MEM);
}

struct Hog createHogFromLine(char* line) {
    char* currCol;
    char* pid;
    char* cpu;
    char* mem;
    int cpuColIndex = 10;

    currCol = strtok(line, " ");
    pid = currCol;

    for (int i = 0; i < cpuColIndex; i++) {
        currCol = strtok(NULL, " ");
    }
    cpu = currCol;

    currCol = strtok(NULL, " ");
    mem = currCol;

    struct Hog h = {atoi(pid), atof(cpu), atof(mem)};
    return h;
}

// TODO: fix
int atEndOfLine(char* line) {
    if (line[sizeof line - 1] == '\0' && line[sizeof line - 2] != '\n') {
        printf("n:%c 0:%c\n", line[sizeof line - 2], line[sizeof line - 1]);
        return -1;
    }
    return 0;   
}

void printHogUsageInstructions() {
    printf("usage: hog [-p] n\n\n");
    printf("     -p: instructs n to specify minimum required percentage of process\n");
    printf("      n: instructs to return n top processes using up %%CPU \n");
    printf("   NOTE: if no -p, n will be floored\n");
}

// -1 = error
// 1 = success and 1 arg (n)
// 2 = success and 2 args (-p n)
int validateArgs(int len, char *argv[]) {
    if (len == 2) {  // validating for hogN
        int n = atoi(argv[1]);
        if (n < 1 || n > MAX_PROCESSES) {
            printf("n must be a nonnegative integer less than or equals to %d, and you inputted %d", MAX_PROCESSES, n);
            return -1;
        }
        return 1;
    } else {  // validating for hogPN
        if (strcmp("-p", argv[1]) != 0) {
            printf("Option unrecognized. Options available to hog include: p\n");
            return -1;
        }
        double n = atoi(argv[2]);
        if (n < 0 || n > 100) {
            printf("Argument n must be between 0 and 100, and you inputted %f", n);
            return -1;
        }
        return 2;
    }
}

void hogN(int n) {
    // TODO
}

void hogPN(double n) {
    FILE* fp = popen("ps -ev", "r");
    char buf[BUFFER_SIZE];
    char* line = (char*)1;
    char* firstline = fgets(buf, BUFFER_SIZE, fp); // <-- uncomment to read and skip first line with labels
    printf("%s\n\n", firstline);
    // for (int i = 0; i < BUFFER_SIZE; i++) {
    //     printf("<%c>", firstline[i]);
    // }
    // printf("\n\n");
    // printf("%s\n", fgets(buf, 78, fp));
    while (line) {
        DIVIDER();
        line = fgets(buf, BUFFER_SIZE, fp);
        printf("LINE: %s\n", line);
        struct Hog h = createHogFromLine(line);
        printHog(h);
        NEWLINE();

        // TODO: have atEndOfLine work
        while (atEndOfLine(line) != 0) {
            line = fgets(buf, BUFFER_SIZE, fp);
            printf("WHILE LOOP: %s\n", line);
        }
        NEWLINE();
    }
}

int main(int argc, char const *argv[]) {
    // printf("%s\n", argv[1]);
    // printf("%d\n", argc);
    // if (argc == 1) {  // print usage instructions
    //     printHogUsageInstructions();
    // } else if (argc == 2) {  // hog n
    //     validateArgs(argc, argv);
    //     hogN();
    // } else if (argc == 3) {  // hog -p n
        
    // } else { 
    //     // Print error and print command to get usage instructions
    // }

    hogPN(2);
    return 0;
}