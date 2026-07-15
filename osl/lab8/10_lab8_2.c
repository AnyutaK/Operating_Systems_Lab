/*Consider the following snapshot of the system. Write C/C++ program to implement deadlock
detection algorithm.

processNo  Allocation Request Available
             A B C     A B C   A B C
P0           0 1 0     0 0 0   0 0 0
P1           2 0 0     2 0 2  
P2           3 0 3     0 0 0
P3           2 1 1     1 0 0
P4           0 0 2     0 0 2

(a) Is the system in a safe state?
(b) Suppose that process P2 make one additional request for instance of type C, can the
system still be in a safe state?*/

#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10 
#define MAX_R 10 

int P, R; 
int Alloc[MAX_P][MAX_R];
int Req[MAX_P][MAX_R];
int Available[MAX_R];

void printFinishStatus(bool finish[]) {
    printf("Process Status:\n");
    for (int i = 0; i < P; i++) {
        printf("P%d: %s\n", i, finish[i] ? "Finished" : "Deadlocked");
    }
}

void detectDeadlock() {
    int work[MAX_R];
    bool finish[MAX_P];
    bool changed;
    int count = 0;
    for (int i = 0; i < R; i++) {
        work[i] = Available[i];
    }
    for (int i = 0; i < P; i++) {
        bool allocEmpty = true;
        for (int j = 0; j < R; j++) {
            if (Alloc[i][j] != 0) {
                allocEmpty = false;
                break;
            }
        }
        finish[i] = allocEmpty;
    }
    do {
        changed = false;
        for (int i = 0; i < P; i++) {
            if (finish[i] == false) {
                bool possible = true;
                for (int j = 0; j < R; j++) {
                    if (Req[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (int j = 0; j < R; j++) {
                        work[j] += Alloc[i][j];
                    }
                    finish[i] = true;
                    changed = true;
                    printf("Process P%d can finish. Resources released: ", i);
                    for(int j=0; j<R; j++) printf("%d ", Alloc[i][j]);
                    printf("\n");
                }
            }
        }
    } while (changed);
    printf("\nFinal System State:\n");
    bool deadlock = false;
    for (int i = 0; i < P; i++) {
        if (finish[i] == false) {
            deadlock = true;
            printf("Process P%d is DEADLOCKED.\n", i);
        }
    }

    if (!deadlock) {
        printf("System is in a SAFE STATE (No Deadlock detected).\n");
    } else {
        printf("System is in an UNSAFE STATE (Deadlock detected).\n");
    }
    printf("\n");
}

int main() {
    printf("Enter number of Processes: ");
    scanf("%d", &P);
    printf("Enter number of Resource types: ");
    scanf("%d", &R);
    printf("\nEnter Allocation Matrix (row-wise):\n");
    for (int i = 0; i < P; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &Alloc[i][j]);
        }
    }
    printf("\nEnter Request Matrix (row-wise):\n");
    for (int i = 0; i < P; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < R; j++) {
            scanf("%d", &Req[i][j]);
        }
    }
    printf("\nEnter Available Resources:\n");
    for (int j = 0; j < R; j++) {
        scanf("%d", &Available[j]);
    }
    printf("\nPart (a): Checking Initial State\n");
    detectDeadlock();
    printf("\nPart (b): P2 requests 1 instance of Resource C\n");
    int resourceC_index = 2; 
    Req[2][resourceC_index] += 1; 
    printf("Updated Request for P2: ");
    for(int j=0; j<R; j++) printf("%d ", Req[2][j]);
    printf("\n");
    detectDeadlock();
    return 0;
}

