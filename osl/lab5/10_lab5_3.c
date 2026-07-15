#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 20

typedef struct {
    int pid;
    int at;
    int bt;
    int deadline;    
    int remt;
    int ct;
    int is_completed;
    int is_active;   
} Process;

int main() {
    Process p[MAX_PROCESSES];
    int n, i;
    int current_time = 0;
    int completed = 0;
    int total_burst = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].is_completed = 0;
        p[i].is_active = 0;
        
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("Enter Absolute Deadline for Process %d: ", i + 1);
        scanf("%d", &p[i].deadline);
        
        p[i].remt = p[i].bt;
        total_burst += p[i].bt;
    }

    printf("\nEDF Simulation Started \n");

    while (completed < n) {
        for (i = 0; i < n; i++) {
            if (p[i].at == current_time && p[i].is_completed == 0) {
                p[i].is_active = 1;
                printf("Time %d: Process %d arrived\n", current_time, p[i].pid);
            }
        }

        int edf_process = -1;
        int min_deadline = 999999; 

        for (i = 0; i < n; i++) {
            if (p[i].is_active == 1 && p[i].is_completed == 0) {
                if (p[i].deadline < min_deadline) {
                    min_deadline = p[i].deadline;
                    edf_process = i;
                }
                else if (p[i].deadline == min_deadline) {
                    if (p[i].at < p[edf_process].at) {
                        edf_process = i;
                    }
                }
            }
        }
        if (edf_process != -1) {
            p[edf_process].remt--;
            if (p[edf_process].remt == 0) {
                p[edf_process].is_completed = 1;
                p[edf_process].ct = current_time + 1;
                completed++;
                
                printf("Time %d: Process %d completed.\n", current_time + 1, p[edf_process].pid);
                if (p[edf_process].ct > p[edf_process].deadline) {
                    printf("Warning: Process %d missed its deadline!\n", p[edf_process].pid);
                }
            }
        } else {
             printf("Time %d: CPU Idle\n", current_time);
        }

        current_time++;
        if (current_time > total_burst + 100) {
            printf("Error: Simulation exceeded expected time. Check input.\n");
            break;
        }
    }
    printf("\nResults\n");
    printf("PID\tAT\tBT\tDead\tCT\tStatus\n");
    for (i = 0; i < n; i++) {
        char* status = (p[i].ct <= p[i].deadline) ? "Met" : "Missed";
        printf("%d\t%d\t%d\t%d\t%d\t%s\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].deadline, p[i].ct, status);
    }

    return 0;
}


//for the sample io, inputs given
//number of processes:3
//p1: arrival time=0, burst time=4,absolute deadline=3
//p2: arrival time=3, burst time=6,absolute deadline=7
//p3: arrival time=5, burst time=8,absolute deadline=8

//for the sample io, inputs given
//number of processes:2
//p1: arrival time=2, burst time=4,absolute deadline=10
//p2: arrival time=5, burst time=7,absolute deadline=20

