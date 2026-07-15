//Create a zombie (defunct) child process (a child with exit() call, but no
//corresponding wait() in the sleeping parent) and allow the init process to adopt it
//(after parent terminates). Run the process as background process and run “ps” command.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork failed");
        return 1;
    } else if (pid == 0) {
        printf("child's PID %d is exiting.\n", getpid());
        exit(0); 
    } else {        
        printf("Parent of PID %d is sleeping for 20 seconds\n", getpid());
        printf("checking 'ps aux' in another terminal now!\n");
        printf("found Zombie status for child process.\n");
        sleep(20); 
        printf("parent process is waking up and exiting.\n");
    }

    return 0;
}