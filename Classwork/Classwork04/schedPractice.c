#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct KeyValue {
    char *key;
    int value;
};

int printKVThreads(struct KeyValue kv[], int size) {
    int limitSubtraction = 0;
    for (int i = 0; i < size; i++) {
        if (kv[i].value > 0 && kv[i].value <= 40) {
            printf("%s:%i:done\n", kv[i].key, kv[i].value);
            kv[i].value -= 40;
            limitSubtraction++;
        } else if (kv[i].value > 40) {
            kv[i].value -= 40;
            printf("%s:40:%i\n", kv[i].key, kv[i].value);
        }
    }
    return limitSubtraction;
}

int main(int argc, char **argv) {
    int quantum = 40;
    int len = argc - 1;
    struct KeyValue kvArr[len / 2];
    int kvCounter = 0;
    for (int i = 1; i < len; i += 2) {
        kvArr[kvCounter].key = argv[i];
        kvArr[kvCounter].value = atoi(argv[i + 1]);
        kvCounter++;
    }

    printf("\nKEY -- thread:used:remaining\n\n");

    int limit = len / 2;
    while (limit > 0) {
        limit -= printKVThreads(kvArr, len / 2);
    }
    return 0;
}