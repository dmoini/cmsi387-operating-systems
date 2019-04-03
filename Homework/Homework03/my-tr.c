#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    pid_t returnedValue = fork();
    if(returnedValue < 0){
        perror("error forking");
        return -1;
    } else if (returnedValue == 0){
        if(close(STDOUT_FILENO) < 0){
            perror("error closing standard output");
            return -1;
    }
        if(open("my-processes", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR) < 0){
            perror("error opening my-processes");
            return -1;
        }
        execlp("tr", "tr", "l", NULL);
        perror("error executing tr");
        return -1;
} else {
        if(waitpid(returnedValue, 0, 0) < 0){
            perror("error waiting for child");
            return -1;
        }
        printf( "Note the parent still has the old standard output." );
    }
}