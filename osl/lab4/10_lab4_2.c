//Write a C program to load the binary executable of the previous program in a child process using exec system call.
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed");
        return 1;
    } else if (pid == 0) {
        printf("child is executing '10_lab4_1' now \n");
        execlp("./10_lab4_1", "10_lab4_1", NULL);
        perror("Exec Failed");
    } else {
        wait(NULL); 
        printf("child has finished executing 10_lab4_1 and control back to parent.\n");
    }

    return 0;
}