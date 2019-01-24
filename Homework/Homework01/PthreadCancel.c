#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

static void *child(void *ignored) {
    while(1) {
        sleep(5);
        printf("Hurry up.\n");
    }
}

int main(int argc, char *argv[]) {
    pthread_t child_thread;
    char str[1];

    pthread_create(&child_thread, NULL, child, NULL);
    printf("Press the ENTER key to cancel this thread.\n");
    scanf("%c", str);
    pthread_cancel(child_thread);
    printf("The thread has been cancelled.");
    return 0;
}