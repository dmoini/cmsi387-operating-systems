#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t returnedValue = fork();
    if (returnedValue < 0) {
        perror("error forking");
        return -1;
    } else if (returnedValue == 0) {
        printf("returnedValue == 0");
        if (close(STDIN_FILENO) < 0) { 
            perror("error closing standard input");
            return -1;
        }
        if (open("/etc/passwd", O_RDONLY, S_IRUSR) < 0) {
            perror("error opening my-processes");
            return -1;
        }
        execlp("tr", "tr", "a-z", "A-Z", NULL);
        perror("error executing tr");
        return -1;
    } else {
        if (waitpid(returnedValue, 0, 0) < 0) {
            perror("error waiting for child");
            return -1;
        }
        printf("\nNote the parent still has the old standard output.\n");
    }
}