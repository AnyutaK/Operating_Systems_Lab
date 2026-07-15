/*Consider the following INSTANCE of the system. Write C/C++ program to implement Banker’s
algorithm for deadlock avoidance. The program has to accept all inputs from the user. Assume
the total number of instances of A,B and C are 10,5 and 7 respectively.

ProcessNo  Allocation  Max   Available
            A B C     A B C   A B C
P0          0 1 0     7 5 3   3 3 2
P1          2 0 0     3 2 2
P2          3 0 2     9 0 2 
P3          2 1 1     2 2 2 
P4          0 0 2     4 3 3

(a) What is the content of the matrix Need?
(b) Is the system in a safe state?
(c) If a request from process P1 arrives for (1, 0, 2), can the request be granted immediately?
Display the updated Allocation, Need and Available matrices.
(d) If a request from process P4 arrives for (3, 3, 0), can the request be granted immediately?
(e) If a request from process P0 arrives for (0, 2, 0), can the request be granted immediately?*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10


int P, R; 
int Alloc[MAX_P][MAX_R];
int Max[MAX_P][MAX_R];
int Need[MAX_P][MAX_R];
int Available[MAX_R];
int SafeSeq[MAX_P];

void calculateNeed() {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            Need[i][j] = Max[i][j] - Alloc[i][j];
        }
    }
}
void printMatrix(const char* title, int mat[MAX_P][MAX_R]) {
    printf("%s:\n", title);
    printf("    ");
    for(int k=0; k<R; k++) printf("%c ", 'A' + k);
    printf("\n");
    for (int i = 0; i < P; i++) {
        printf("P%d  ", i);
        for (int j = 0; j < R; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void printAvailable() {
    printf("Available Resources: ");
    for (int j = 0; j < R; j++) printf("%d ", Available[j]);
    printf("\n\n");
}
bool isSafe() {
    int work[MAX_R];
    bool finish[MAX_P];
    for (int i = 0; i < R; i++) work[i] = Available[i];
    for (int i = 0; i < P; i++) finish[i] = false;
    int count = 0;
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (finish[i] == false) {
                bool possible = true;
                for (int j = 0; j < R; j++) {
                    if (Need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < R; j++)
                        work[j] += Alloc[i][j];
                    
                    SafeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) return false; 
    }
    return true;
}

bool requestResources(int pID, int req[]) {
    printf("\nProcessing request from P%d for (", pID);
    for(int i=0; i<R; i++) printf("%d ", req[i]);
    printf(")\n");
    for (int i = 0; i < R; i++) {
        if (req[i] > Need[pID][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }
    for (int i = 0; i < R; i++) {
        if (req[i] > Available[i]) {
            printf("Not enough resources.\n");
            return false;
        }
    }
    for (int i = 0; i < R; i++) {
        Available[i] -= req[i];
        Alloc[pID][i] += req[i];
        Need[pID][i] -= req[i];
    }
    if (isSafe()) {
        printf("Request GRANTED. System in safe state.\n");
        printf("Safe Sequence: ");
        for(int i=0; i<P; i++) printf("P%d ", SafeSeq[i]);
        printf("\n");
        return true;
    } else {
        printf("Request DENIED. Would cause an unsafe state.\n");
        for (int i = 0; i < R; i++) {
            Available[i] += req[i];
            Alloc[pID][i] -= req[i];
            Need[pID][i] += req[i];
        }
        return false;
    }
}

int main() {
    printf("Enter number of Processes: ");
    scanf("%d", &P);
    printf("Enter number of Resource types: ");
    scanf("%d", &R);
    printf("Enter Allocation Matrix (row-wise):\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &Alloc[i][j]);
        }
    }
    printf("Enter Max Matrix (row-wise):\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &Max[i][j]);
        }
    }
    printf("Enter Available Resources: ");
    for (int i = 0; i < R; i++) {
        scanf("%d", &Available[i]);
    }
    calculateNeed();
    printf("\n(a) Content of Matrix Need:\n");
    printMatrix("Need Matrix", Need);
    printf("(b) Checking Safety State\n");
    if (isSafe()) {
        printf("System in safe state\n");
        printf("Safe Sequence: ");
        for(int i=0; i<P; i++) printf("P%d ", SafeSeq[i]);
        printf("\n");
    } else {
        printf("System NOT in safe state.\n");
    }

    // (c) Request from P1 (1, 0, 2)
    int req1[] = {1, 0, 2};
    bool granted = requestResources(1, req1);
    if(granted) {
        printf("Updated matrices for part (c):\n");
        printMatrix("Allocation", Alloc);
        printMatrix("Need", Need);
        printAvailable();
    }

    // (d) Request from P4 (3, 3, 0)
    int req2[] = {3, 3, 0};
    requestResources(4, req2);

    // (e) Request from P0 (0, 2, 0)
    int req3[] = {0, 2, 0};
    requestResources(0, req3);

    return 0;
}