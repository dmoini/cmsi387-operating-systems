#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define NEWLINE() printf("\n");
#define DIVIDER() printf("============================================================================\n");
#define PL(l) printf("LINE: %s\n", l);

enum { MAX_PROCESSES = 20 };
enum { BUFFER_SIZE = 1024 };

typedef struct {
    int PID;
    double CPU;
    double MEM;
} Hog;

void printColumnNames() {
    printf("PID\t\t%%CPU\t\t%%MEM\n");
}

void printHog(Hog h) {
    printf("%d\t\t%.1f\t\t%.1f\n", h.PID, h.CPU, h.MEM);
}

Hog createHogFromLine(char* line) {
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

    Hog h = {atoi(pid), atof(cpu), atof(mem)};
    return h;
}

int notEndOfLine(const char* line) {
    return strchr(line, '\n') == NULL;
}

void printHogUsageInstructions() {
    printf("\nusage: hog [-p] n\n\n");
    printf("     -p: instructs n to specify minimum required percentage of process\n");
    printf("      n: instructs to return n top processes using up %%CPU, in descending order \n");
    printf("   NOTE: if no -p, n will be floored\n\n");
}

// -1 = error
// 0 = valid arguments
int validateArgs(int len, char const* argv[]) {
    if (len == 2) {  // validating for hogN
        int n = atoi(argv[1]);
        if (n < 1 || n > MAX_PROCESSES) {
            printf("n must be a nonnegative integer less than or equal to %d. You inputted %d\n", MAX_PROCESSES, n);
            return -1;
        }
        return 0;
    } else {  // validating for hogPN
        if (strcmp("-p", argv[1]) != 0) {
            printf("Option unrecognized.\n");
            printHogUsageInstructions();
            return -1;
        }

        double n = atoi(argv[2]);
        if (n < 0) {
            printf("Argument n must be a nonnegative double. You inputted %f", n);
            return -1;
        }
        return 0;
    }
}

void prefillTop(Hog top[], int n) {
    for (int i = 0; i  < n; i++) {
        Hog h = {-1, -1, -1};
        top[i] = h;
    }
}

void printTop(Hog top[], int n) {
    for (int i = 0; i < n; i++) {
        printHog(top[i]);
    }
}

int compareCPU(const void *h1, const void *h2) {
    const Hog *hogA = h1;
    const Hog *hogB = h2;
    return (hogA->CPU < hogB->CPU) - (hogA->CPU > hogB->CPU);
}

void hogN(int n) {
    Hog top[n];
    prefillTop(top, n);
    
    FILE* fp = popen("ps -ev", "r");
    char buf[BUFFER_SIZE];
    char* line = fgets(buf, BUFFER_SIZE, fp); // skips first line (column names)
    printColumnNames();
    while ((line = fgets(buf, BUFFER_SIZE, fp))) {
        Hog h = createHogFromLine(line);
        if (h.CPU > top[n - 1].CPU) {
            top[n - 1] = h;
            qsort(top, n, sizeof(Hog), compareCPU);
        }
        while (notEndOfLine(line)) {
            line = fgets(buf, BUFFER_SIZE, fp);
        }
    }
    printTop(top, n);
}

void hogPN(double n) {
    FILE* fp = popen("ps -ev", "r");
    char buf[BUFFER_SIZE];
    char* line = fgets(buf, BUFFER_SIZE, fp); // skips first line (column names)
    printColumnNames();
    while ((line = fgets(buf, BUFFER_SIZE, fp))) {
        Hog h = createHogFromLine(line);
        if (h.CPU >= n) {
            printHog(h);
        }
        while (notEndOfLine(line)) {
            line = fgets(buf, BUFFER_SIZE, fp);
        }
    }
}

int main(int argc, char const* argv[]) {
    if (argc == 1) {
        printHogUsageInstructions();
        return -1;
    } else if (argc == 2) {
        if (validateArgs(argc, argv) == -1) {
            return -1;
        };
        hogN(atoi(argv[1]));
    } else if (argc == 3) {
        if (validateArgs(argc, argv) == -1) {
            return -1;
        }
        hogPN(atof(argv[2]));
    } else { 
        printf("Too many arguments.\n");
        printHogUsageInstructions();
        return -1;
    }
    return 0;
}