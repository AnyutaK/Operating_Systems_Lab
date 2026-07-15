//Write a C program to create a child process. Display different messages in parent
//process and child process. Display PID and PPID of both parent and child process.
//Block parent process until child completes using wait system call.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){

pid_t pid;
pid=fork();
if (pid<0){
	fprintf(stderr, "fork failed "); return 1;
}
else if (pid == 0) {
        printf("this is child process.\n");
        printf("Child PID: %d\n", getpid());       
        printf("Child PPID: %d\n", getppid());     
    } 
    else {
        wait(NULL); 
        
        printf("this is parent process.\n");
        printf("Parent PID: %d\n", getpid());
        printf("Parent PPID: %d\n", getppid());
    }

    return 0;
}