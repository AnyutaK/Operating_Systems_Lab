/*Write a multithreaded program that implements the banker's algorithm. Create n threads that
request and release resources from the bank. The banker will grant the request only if it leaves
the system in a safe state. You may write this program using either Pthreads. It is important
that shared data be safe from concurrent access. To ensure safe access to shared data, you
can use mutex locks, which are available in the Pthreads libraries*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#define MAX_C 10
#define MAX_R 10

int C;
int R;
int avail[MAX_R];
int max[MAX_C][MAX_R];
int alloc[MAX_C][MAX_R];
int need[MAX_C][MAX_R];
pthread_mutex_t mutex;
void calc_need() {
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}
void print_state() {
    printf("\nCurrent System State\n");
    printf("Available: [");
    for (int i = 0; i < R; i++) {
        printf("%d ", avail[i]);
    }
    printf("]\n");
    
    printf("PID | Allocation | Need      | Max\n");
    for(int i=0; i<C; i++) {
        printf("P%d  | ", i);
        for(int j=0; j<R; j++) printf("%d ", alloc[i][j]);
        printf("| ");
        for(int j=0; j<R; j++) printf("%d ", need[i][j]);
        printf("| ");
        for(int j=0; j<R; j++) printf("%d ", max[i][j]);
        printf("\n");
    }
    printf("_____________________________\n");
}
int is_safe() {
    int work[MAX_R];
    int fin[MAX_C] = {0};
    int safe_seq[MAX_C];
    int count = 0;

    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    while (count < C) {
        int found = 0;
        for (int i = 0; i < C; i++) {
            if (fin[i] == 0) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == R) {
                    for (int k = 0; k < R; k++)
                        work[k] += alloc[i][k];
                    
                    fin[i] = 1;
                    safe_seq[count++] = i;
                    found = 1;
                }
            }
        }
        if (!found) return 0;
    }
    return 1;
}
int request_resources(int cn, int req[]) {
    for (int i = 0; i < R; i++) {
        if (req[i] > need[cn][i]) {
            printf("Error: P%d exceeded maximum claim.\n", cn);
            return 0;
        }
    }

    for (int i = 0; i < R; i++) {
        if (req[i] > avail[i]) {
            printf("P%d:Not enough available resources.\n", cn);
            return 0; 
        }
    }

    for (int i = 0; i < R; i++) {
        avail[i] -= req[i];
        alloc[cn][i] += req[i];
        need[cn][i] -= req[i];
    }

    if (is_safe()) {
        printf("P%d: Request GRANTED. System safe.\n", cn);
        return 1;
    } else {
        printf("P%d: Request DENIED (Unsafe state). Rolling back.\n", cn);
        for (int i = 0; i < R; i++) {
            avail[i] += req[i];
            alloc[cn][i] -= req[i];
            need[cn][i] += req[i];
        }
        return 0;
    }
}
void release_resources(int cn) {
    printf("P%d: Releasing all resources.\n", cn);
    for (int i = 0; i < R; i++) {
        avail[i] += alloc[cn][i];
        alloc[cn][i] = 0;
        need[cn][i] = max[cn][i]; 
    }
}
void *customer_loop(void *arg) {
    int pid = *(int *)arg;
    int req[MAX_R];
    srand(time(NULL) + pid);
    int iti = 0;
    while (iti < 5) {
        sleep(1);
        int needs_resources = 0;
        for (int i = 0; i < R; i++) {
            if (need[pid][i] > 0) needs_resources = 1;
            
            if (need[pid][i] > 0)
                req[i] = rand() % (need[pid][i] + 1); 
            else
                req[i] = 0;
        }
        if (needs_resources) {
            pthread_mutex_lock(&mutex);
            
            printf("\nP%d requesting resources: [", pid);
            for(int i=0; i<R; i++) printf("%d ", req[i]);
            printf("]\n");

            request_resources(pid, req);
            
            pthread_mutex_unlock(&mutex);
        } else {
            pthread_mutex_lock(&mutex);
            release_resources(pid);
            print_state();
            pthread_mutex_unlock(&mutex);
            break; 
        }
        iti++;
    }
    free(arg);
    pthread_exit(NULL);
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    printf("Enter number of Customers (Processes): ");
    scanf("%d", &C);
    printf("Enter number of Resource Types: ");
    scanf("%d", &R);
    printf("Enter Available Resources: ");
    for (int i = 0; i < R; i++) scanf("%d", &avail[i]);
    printf("Enter Max Matrix:\n");
    for (int i = 0; i < C; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < R; j++) scanf("%d", &max[i][j]);
    }
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < C; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < R; j++) scanf("%d", &alloc[i][j]);
    }
    calc_need();
    pthread_mutex_lock(&mutex);
    if (!is_safe()) {
        printf("Initial state UNSAFE! Exiting.\n");
        return -1;
    }
    printf("Initial state SAFE.\n");
    print_state();
    pthread_mutex_unlock(&mutex);
    pthread_t threads[C];
    for (int i = 0; i < C; i++) {
        int *pid = malloc(sizeof(int));
        *pid = i;
        if (pthread_create(&threads[i], NULL, customer_loop, (void *)pid) != 0) {
            perror("Failed to create thread");
        }
    }
    for (int i = 0; i < C; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("\nAll customers finished execution.\n");
    pthread_mutex_destroy(&mutex);
    return 0;
}
