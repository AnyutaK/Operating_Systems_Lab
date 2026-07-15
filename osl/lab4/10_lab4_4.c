//Write a multithreaded program that performs different sorting algorithms.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

typedef struct {
    int *array;
    int size;
    const char *algo;
} SortTask;

void print_array(int *arr, int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void* bubble(void* arg) {
    SortTask *task = (SortTask*)arg;
    int n = task->size;
    int *arr = task->array;
    clock_t start = clock();

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("[%s] finished in %f seconds.\n", task->algo, time);
    pthread_exit(NULL);
}

void* selection(void* arg) {
    SortTask *task = (SortTask*)arg;
    int n = task->size;
    int *arr = task->array;
    clock_t start = clock();

    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx]) min_idx = j;
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }

    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("[%s] finished in %f seconds.\n", task->algo, time);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <num_elements> \n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (argc != n + 2) {
        printf("Error: Expected %d elements, but got %d.\n", n, argc - 2);
        return 1;
    }

    int *og_arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) og_arr[i] = atoi(argv[i + 2]);

    int *copy1 = malloc(n * sizeof(int));
    int *copy2 = malloc(n * sizeof(int));
    memcpy(copy1, og_arr, n * sizeof(int));
    memcpy(copy2, og_arr, n * sizeof(int));

    pthread_t thread1, thread2;
    SortTask task1 = {copy1, n, "Bubble Sort"};
    SortTask task2 = {copy2, n, "Selection Sort"};

    pthread_create(&thread1, NULL, bubble, &task1);
    pthread_create(&thread2, NULL, selection, &task2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("\nFinal Sorted Array: ");
    print_array(copy1, n);

    free(og_arr);
    free(copy1);
    free(copy2);
    return 0;
}
