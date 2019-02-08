#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

struct KeyValue {
    char* key;
    int value;
};

int main(int argc, char *argv[]) {
    int quantum = 40;
    typedef struct KeyValue KeyValue;
    KeyValue *kp[argc - 1];
    

    for (int i = 1; i < argc; i += 2) {
        struct KeyValue kv;
        kv.key = argv[i];
        kv.value = argv[i + 1];
    }

    printf("%s %s", argv[1], argv[2]);
    // printf("%d", argc);
    return 0;
}