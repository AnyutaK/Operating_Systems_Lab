//Write a C/C++ program for Dining-Philosophers problem using semaphores.

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#define N 5 
#define Eat_count 3
sem_t chopstick[N];

void* philosopher(void* arg) {
    int id = *(int*)arg;
    int i=0;
    while(i<Eat_count) {
        printf("philosopher %d thinking\n", id + 1);
        sleep(1);
        if (id == N - 1) {
            sem_wait(&chopstick[(id + 1) % N]); 
            sem_wait(&chopstick[id]);
        } else {
            sem_wait(&chopstick[id]);
            sem_wait(&chopstick[(id + 1) % N]);
        }
        printf("philosopher %d eating\n", id + 1);
        sleep(2);
        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id + 1) % N]);
        printf("philosopher %d has finished eatin and put down chopsticks.\n", id + 1);
        i++;
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];
    for (int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
    }
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopstick[i]);
    }
    return 0;
}