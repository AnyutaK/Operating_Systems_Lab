//Write multithreaded program that generates the Fibonacci series.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *fib; 
int n;

void *gen_fib(void *arg) {
    int f = 0, s = 1, t;

    for (int i = 0; i < n; i++) {
        if (i <= 1)
            t = i;
        else {
            t = f + s;
            f = s;
            s = t;
        }
        fib[i] = t;
    }
    pthread_exit(NULL);
}

int main(int argc, char *seq[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_terms>\n", seq[0]);
        return 1;
    }

    n = atoi(seq[1]);
    fib = (int *)malloc(n * sizeof(int));

    pthread_t tid;
    pthread_create(&tid, NULL, gen_fib, NULL);
    pthread_join(tid, NULL);
    printf("Fibonacci Series: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");
    free(fib);
    return 0;
}