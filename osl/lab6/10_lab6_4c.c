#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok(".", 66);
    int shmid = shmget(key, SHM_SIZE, 0666); 
    char *shm = (char*) shmat(shmid, NULL, 0);
    printf("Consumer: Reading from shared memory...\n");
    printf("Consumer: Data = \"%s\"\n", shm);
    shmdt(shm);
    printf("Consumer: Detached.\n");
    return 0;
}