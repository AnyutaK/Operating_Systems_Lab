/*Write a C/C++ Program to simulate the following algorithms find the total no. of cylinder
movements for various input requests
(i) FCFS (ii) SSTF (iii) SCAN (iv) C-SCAN
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int compare (const void *a , const void *b){
	return (*(int *)a- *(int *)b);
}
void printPath(int start, int *arr, int size, int jump_to){
	printf("%d",start);
	if (jump_to !=-1){
		printf(" ->%d",jump_to); start = jump_to;
	}
	for(int i=0;i<size;i++){
		printf (" -> %d", arr[i]);
	} printf("/n");
}
int calculateFCFS(int *queue, int n, int head) {
    int mvmt = 0;
    int cur = head;
    printf("\nFCFS Path:\n");
    printPath(head, queue, n, -1);
    for (int i = 0; i < n; i++) {
        mvmt += abs(cur - queue[i]);
        cur = queue[i];
    }
    return mvmt;
}
int calculateSSTF(int *queue, int n, int head) {
    int mvmt = 0;
    int cur = head;
    int *visited = (int *)calloc(n, sizeof(int)); 
    int *path = (int *)malloc(n * sizeof(int));
    for (int count = 0; count < n; count++) {
        int min_dist = 999999;
        int next_idx = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && abs(cur - queue[i]) < min_dist) {
                min_dist = abs(cur - queue[i]);
                next_idx = i;
            }
        }
        visited[next_idx] = 1;
        path[count] = queue[next_idx];
        mvmt += min_dist;
        cur = queue[next_idx];
    }
    printf("\nSSTF Path:\n");
    printPath(head, path, n, -1);
    free(visited);
    free(path);
    return mvmt;
}
int calculateSCAN(int *queue, int n, int head, int max_cyl, int dir){
	int *left = (int *)malloc((n + 1) * sizeof(int));
    int *right = (int *)malloc((n + 1) * sizeof(int));
    int l_count = 0, r_count = 0;
    for (int i = 0; i < n; i++) {
        if (queue[i] < head)
            left[l_count++] = queue[i];
        else
            right[r_count++] = queue[i];
    }
    if (dir == 1)
        right[r_count++] = max_cyl;
    else
        left[l_count++] = 0;
    qsort(left, l_count, sizeof(int), compare);
    qsort(right, r_count, sizeof(int), compare);
    int mvmt = 0;
    int cur = head;
    int *path = (int *)malloc((n + 1) * sizeof(int));
    int path_idx = 0;
    if (dir == 1) {
        for (int i = 0; i < r_count; i++) path[path_idx++] = right[i];
        for (int i = l_count - 1; i >= 0; i--) path[path_idx++] = left[i];
    } else {
        for (int i = l_count - 1; i >= 0; i--) path[path_idx++] = left[i];
        for (int i = 0; i < r_count; i++) path[path_idx++] = right[i];
    }
    printf("\nSCAN Path:\n");
    printPath(head, path, path_idx, -1);
    for (int i = 0; i < path_idx; i++) {
        mvmt += abs(cur - path[i]);
        cur = path[i];
    }
    free(left);
    free(right);
    free(path);
    return mvmt;
}
int calculateCSCAN(int *queue, int n, int head, int max_cyl, int dir) {
    int *left = (int *)malloc((n + 1) * sizeof(int));
    int *right = (int *)malloc((n + 1) * sizeof(int));
    int l_count = 0, r_count = 0;
    for (int i = 0; i < n; i++) {
        if (queue[i] < head)
            left[l_count++] = queue[i];
        else
            right[r_count++] = queue[i];
    }
    right[r_count++] = max_cyl;left[l_count++] = 0;
    qsort(left, l_count, sizeof(int), compare);
    qsort(right, r_count, sizeof(int), compare);
    int mvmt = 0; int cur = head;
    int *path = (int *)malloc((n + 2) * sizeof(int));
    int path_idx = 0;
    if (dir == 1) {
        for (int i = 0; i < r_count; i++) path[path_idx++] = right[i];
        for (int i = 0; i < l_count; i++) path[path_idx++] = left[i];
        printf("\nC-SCAN Path:\n");
        printf("%d -> %d | 0 -> ", head, max_cyl);
        for (int i = 0; i < l_count; i++) {
            if(i != 0) printf(" -> ");
            printf("%d", left[i]);
        }
        printf("\n");
    } else {
        for (int i = l_count - 1; i >= 0; i--) path[path_idx++] = left[i];
        for (int i = r_count - 1; i >= 0; i--) path[path_idx++] = right[i];
        printf("\nC-SCAN Path:\n");
        printf("%d -> 0 | %d -> ", head, max_cyl);
        for (int i = 0; i < r_count - 1; i++) {
            if(i != 0) printf(" -> ");
            printf("%d", right[i]);
        }
        printf("\n");
    }
    for (int i = 0; i < path_idx; i++) {
        mvmt += abs(cur - path[i]);
        cur = path[i];
    }
    free(left);
    free(right);
    free(path);
    return mvmt;
}
int main() {
    int n, head, max_cyl, dir;
    printf("\nDisk Scheduling Simulation \n");
    printf("Enter total number of cylinders (e.g., 200): ");
    scanf("%d", &max_cyl);
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    int *queue = (int *)malloc(n * sizeof(int));
    printf("Enter the disk request queue (space separated): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter initial direction of head (1 for Right/High, 0 for Left/Low): ");
    scanf("%d", &dir);
    printf("\n__________________________________________________");
    int fcfs = calculateFCFS(queue, n, head);
    printf("Total Cylinder Movements (FCFS) : %d\n", fcfs);
    printf("__________________________________________________");
    int sstf = calculateSSTF(queue, n, head);
    printf("Total Cylinder Movements (SSTF) : %d\n", sstf);
    printf("__________________________________________________");
    int scan = calculateSCAN(queue, n, head, max_cyl, dir);
    printf("Total Cylinder Movements (SCAN) : %d\n", scan);
    printf("__________________________________________________");
    int cscan = calculateCSCAN(queue, n, head, max_cyl, dir);
    printf("Total Cylinder Movements (C-SCAN): %d\n", cscan);
    printf("__________________________________________________");
    free(queue);
    return 0;
}
