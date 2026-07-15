#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

struct shared_data {
    char ch;
    int status;
};

int main() {
    key_t key = ftok(".", 65); 
    int shmid = shmget(key, sizeof(struct shared_data), 0666);
    if (shmid == -1) {
        perror("shmget failed. Ensure Parent is running in the same folder!");
        exit(1);
    }
    struct shared_data *shm = (struct shared_data*) shmat(shmid, NULL, 0);
    printf("Waiting for Parent to write data...\n");
    fflush(stdout);
    while(shm->status != 1) {
        sleep(1); 
    }
    char c = shm->ch;
    printf("child Received '%c'. Calculating...\n", c);
    fflush(stdout);
    if (c == 'z') c = 'a';
    else if (c == 'Z') c = 'A';
    else c++;
    shm->ch = c;
    shm->status = 2; 
    printf("Child Sent reply '%c'.\n", shm->ch);
    fflush(stdout);
    shmdt(shm);
    return 0;
}