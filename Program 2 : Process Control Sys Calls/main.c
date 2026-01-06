#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char* argv[]){

    if (argc < 2) {
        printf("Usage: %s <value>\n", argv[0]);
        exit(1);
    }

    pid_t p = fork();
    int retval;

    if (p < 0){
        printf("Error creating a child process");
        exit(1);
    }

    else if (p == 0){
        printf("pid of child : %d, pid of parent : %d \n", getpid(), getppid());
        execl("./binsearch", "binsearch", argv[1], NULL);
            perror("execl");
            exit(1);
    }
    
    else {
        printf ("pid : %d \n", getpid());
        wait (&retval);
        if (WIFEXITED(retval))
            printf ("Child terminated normally \n");
        else {
            printf("Child terminated abnormally \n");
        }
        exit(0);
    }
    return 0;
}
