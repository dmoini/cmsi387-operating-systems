#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define NEWLINE() printf("\n");
#define DIVIDER() printf("============================================================================\n");
#define PL(l) printf("LINE: %s\n", l);

enum { MAX_PROCESSES = 20 };
enum { BUFFER_SIZE = 1024 };

struct Hog {
    int PID;
    double CPU;
    double MEM;
    // char COMMAND[1021];  // may delete, idk
};

// TODO: update printing format to match columns
void printHog(struct Hog h) {
    printf("PID: %d  \t\t%%CPU: %.1f  \t\t%%MEM: %.1f\n", h.PID, h.CPU, h.MEM);
}

struct Hog createHogFromLine(char* line) {
    char* currCol;
    char* pid;
    char* cpu;
    char* mem;
    int cpuColIndex = 10;
    char localLine[BUFFER_SIZE];

    for (int i = 0; i < BUFFER_SIZE; i++) {
        localLine[i] = line[i];
    }

    currCol = strtok(localLine, " ");
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

int notEndOfLine(const char* line) {
    return strchr(line, '\n') == NULL;
}

void printHogUsageInstructions() {
    printf("\nusage: hog [-p] n\n\n");
    printf("     -p: instructs n to specify minimum required percentage of process\n");
    printf("      n: instructs to return n top processes using up %%CPU \n");
    printf("   NOTE: if no -p, n will be floored\n\n");
}

// -1 = error
// 0 = valid arguments
int validateArgs(int len, char const* argv[]) {
    if (len == 2) {  // validating for hogN
        int n = atoi(argv[1]);
        if (n < 1 || n > MAX_PROCESSES) {
            printf("n must be a nonnegative integer less than or equals to %d, and you inputted %d\n", MAX_PROCESSES, n);
            return -1;
        }
        return 0;
    } else {  // validating for hogPN
        if (strcmp("-p", argv[1]) != 0) {
            printf("Option unrecognized. Options available for hog include: p\n");
            return -1;
        }
        double n = atoi(argv[2]);
        if (n < 0 || n > 100) {
            printf("Argument n must be between 0 and 100, and you inputted %f", n);
            return -1;
        }
        return 0;
    }
}

void hogN(int n) {
    // TODO
}

void hogPN(double n) {
    FILE* fp = popen("ps -ev", "r");
    char buf[BUFFER_SIZE];
    // char* line = (char*)1;
    char* line = fgets(buf, BUFFER_SIZE, fp); // <-- uncomment to read and skip first line with labels
    printf("%s\n", line);
    while ((line = fgets(buf, BUFFER_SIZE, fp))) {
        // DIVIDER();
        // line = fgets(buf, BUFFER_SIZE, fp);
        // PL(line);
        struct Hog h = createHogFromLine(line);
        if (h.CPU >= n) {
            printHog(h);
        }
        // NEWLINE();

        // printf("ICL: %d\n", notEndOfLine(line));
        while (notEndOfLine(line)) {
            line = fgets(buf, BUFFER_SIZE, fp);
            // printf("WHILE LOOP: %s\n", line);
            // printf("ICL: %d\n", notEndOfLine(line));
        }
        // PL("END OF LINE");
        // NEWLINE();
    }
}

int main(int argc, char const* argv[]) {
    // printf("%s\n", argv[1]);
    // printf("%d\n", argc);
    if (argc == 1) {  // print usage instructions
        printHogUsageInstructions();
        return -1;
    } else if (argc == 2) {  // hog n
        if (validateArgs(argc, argv) == -1) {
            return -1;
        };
        printf("hogN()\n");
        // int n = atoi(argv[1]);
        // printf("n: %d\n", n);
        hogN(atoi(argv[1]));
        printf("done\n");
    } else if (argc == 3) {  // hog -p n
        if (validateArgs(argc, argv) == -1) {
            return -1;
        }
        printf("hogPN()\n");
        hogPN(atof(argv[2]));
        printf("done\n");
    } else { 
        printHogUsageInstructions();
        return -1;
    }

    // hogPN(1);
    return 0;
}