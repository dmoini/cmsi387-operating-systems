#include <unistd.h>
#include <stdio.h> 
#include <fcntl.h>
#include <sys/stat.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

// issues: replacing characters with t and spaces with e

int main(){
    pid_t returnedValue = fork();
    // printf("returnedValue: %d\n", returnedValue);
    if (returnedValue < 0) {
        perror("error forking");
        return -1;
    } else if (returnedValue == 0) {
        printf("returnedValue == 0");
        if (close(STDIN_FILENO) < 0) {  // STDOUT_FILENO
            perror("error closing standard input");
            return -1;
        }
        if (open("test.txt", O_RDONLY, S_IRUSR) < 0) {
            perror("error opening my-processes");
            return -1;
        }
        printf("Before execlp");
        execlp("tr", "tr", "a-z A-Z", "test.txt", NULL);
        perror("error executing tr");
        return -1;
    } else {
        if (waitpid(returnedValue, 0, 0) < 0) {
            perror("error waiting for child");
            return -1;
        }
        printf( "Note the parent still has the old standard output.\n" );
    }
}