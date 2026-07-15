#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok(".", 66);
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    char *shm = (char*) shmat(shmid, NULL, 0);
    printf("Producer: Enter a set of words: ");
    fgets(shm, SHM_SIZE, stdin); 
    printf("Producer: Data written to shared memory.\n");
    printf("Producer: Waiting for consumer to read (Press Enter to detach & delete)...\n");
    getchar(); 
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    printf("Producer: Shared memory detached and deleted.\n");
    return 0;
}