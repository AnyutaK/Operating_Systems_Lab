#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
void calculateLOOK(int requests[], int n, int head, int direction) {
    int *left = (int *)malloc(n * sizeof(int));
    int *right = (int *)malloc(n * sizeof(int));
    int left_count = 0, right_count = 0;
    int seek_count = 0;
    int curr_track = head;
    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[left_count++] = requests[i];
        else
            right[right_count++] = requests[i];
    }
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);
    printf("\n--- LOOK Algorithm ---\n");
    printf("Head Movement Sequence: %d", curr_track);
    int run = 2;
    while (run--) {
        if (direction == 1) { 
            for (int i = 0; i < right_count; i++) {
                int next_track = right[i];
                printf(" -> %d", next_track);
                seek_count += abs(next_track - curr_track);
                curr_track = next_track;
            }
            direction = 0; 
        } 
        else { 
            for (int i = left_count - 1; i >= 0; i--) {
                int next_track = left[i];
                printf(" -> %d", next_track);
                seek_count += abs(next_track - curr_track);
                curr_track = next_track;
            }
            direction = 1;
        }
    }
    printf("\nTotal Cylinder Movements (LOOK): %d\n", seek_count);
    free(left);
    free(right);
}
void calculateCLOOK(int requests[], int n, int head, int direction) {
    int *left = (int *)malloc(n * sizeof(int));
    int *right = (int *)malloc(n * sizeof(int));
    int left_count = 0, right_count = 0;
    int seek_count = 0;
    int curr_track = head;
    for (int i = 0; i < n; i++) {
        if (requests[i] < head)
            left[left_count++] = requests[i];
        else
            right[right_count++] = requests[i];
    }
    qsort(left, left_count, sizeof(int), compare);
    qsort(right, right_count, sizeof(int), compare);
    printf("\n--- C-LOOK Algorithm ---\n");
    printf("Head Movement Sequence: %d", curr_track);
    if (direction == 1) { 
        for (int i = 0; i < right_count; i++) {
            int next_track = right[i];
            printf(" -> %d", next_track);
            seek_count += abs(next_track - curr_track);
            curr_track = next_track;
        }
        if (left_count > 0) {
            printf(" -> %d", left[0]);
            seek_count += abs(left[0] - curr_track);
            curr_track = left[0];
        }
        for (int i = 1; i < left_count; i++) {
            int next_track = left[i];
            printf(" -> %d", next_track);
            seek_count += abs(next_track - curr_track);
            curr_track = next_track;
        }
    } 
    else { 
        for (int i = left_count - 1; i >= 0; i--) {
            int next_track = left[i];
            printf(" -> %d", next_track);
            seek_count += abs(next_track - curr_track);
            curr_track = next_track;
        }
        if (right_count > 0) {
            printf(" -> %d", right[right_count - 1]);
            seek_count += abs(right[right_count - 1] - curr_track);
            curr_track = right[right_count - 1];
        }
        for (int i = right_count - 2; i >= 0; i--) {
            int next_track = right[i];
            printf(" -> %d", next_track);
            seek_count += abs(next_track - curr_track);
            curr_track = next_track;
        }
    }
    printf("\nTotal Cylinder Movements (C-LOOK): %d\n", seek_count);
    free(left);
    free(right);
}
int main() {
    int n, head, direction;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int *requests = (int *)malloc(n * sizeof(int));
    printf("Enter the request queue (cylinder numbers): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("Enter the initial direction of head (1 for Right/High, 0 for Left/Low): ");
    scanf("%d", &direction);
    calculateLOOK(requests, n, head, direction);
    calculateCLOOK(requests, n, head, direction);
    free(requests);
    return 0;
}