//Write a C/C++ program for first readers-writers problem using semaphores.

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
sem_t mutex, wrt;
int rc = 0;

void* writer(void* arg) {
    int id = *(int*)arg;
    sem_wait(&wrt);
    printf("writer %d is writing \n", id);
    sleep(1); 
    sem_post(&wrt); 
    printf("writer %d has finished writing\n", id);
    return NULL;
}

void* reader(void* arg) {
    int id = *(int*)arg;
    sem_wait(&mutex); 
    rc++;
    if (rc == 1) {
        sem_wait(&wrt);
    }
    sem_post(&mutex); 
    printf("Reader %d is reading (Total Readers: %d)\n", id, rc);
    sleep(1);
    sem_wait(&mutex);
    rc--;
    if (rc == 0) {
        sem_post(&wrt);
    }
    sem_post(&mutex); 
    printf("Reader %d has finished reading\n", id);
    return NULL;
}

int main() {
    pthread_t threads[5];
    int ids[] = {1, 1, 2, 2, 3}; 
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);
    printf("Creating Reader 1\n");
    pthread_create(&threads[0], NULL, reader, &ids[0]);
    sleep(1); 
    printf("Creating Writer 1\n");
    pthread_create(&threads[1], NULL, writer, &ids[1]);
    printf("Creating Reader 2\n");
    pthread_create(&threads[2], NULL, reader, &ids[2]);
    printf("Creating Writer 2\n");
    pthread_create(&threads[3], NULL, writer, &ids[3]);
    printf("Creating Reader 3\n");
    pthread_create(&threads[4], NULL, reader, &ids[4]);
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}