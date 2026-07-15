#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 20
#define MAX_QUEUE 100

typedef struct {
    int pid;
    int at;       
    int bt;       
    int remt;     
    int wt;       
    int tat;      
    int qlvl;     
    int ct;       
} Process;

int readyQ[MAX_QUEUE];
int qc = 0;
void enqueue(int pid) {
    if (qc >= MAX_QUEUE) return;
    readyQ[qc++] = pid;
}
void remove_from_queue(int index) {
    for (int i = index; i < qc - 1; i++) {
        readyQ[i] = readyQ[i + 1];
    }
    qc--;
}

int get_highest_priority_process(Process p[]) {
    if (qc == 0) return -1;

    int min_level = 999;
    int best_index = -1;

    for (int i = 0; i < qc; i++) {
        if (p[readyQ[i]].qlvl < min_level) {
            min_level = p[readyQ[i]].qlvl;
            best_index = i;
        }
    }
    return best_index;
}

int main() {
    Process p[MAX_PROCESSES];
    int n, i;
    int time_quantum[3] = {4, 8, 100000}; 
    int completed = 0;
    int current_time = 0;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time for Process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for Process %d: ", i + 1);
        scanf("%d", &p[i].bt);
        
        p[i].remt = p[i].bt;
        p[i].qlvl = 0; 
        p[i].wt = 0;
        p[i].ct = 0;
    }

    int rp = -1; 
    int sc = 0;    
    while (completed < n) {
        for (i = 0; i < n; i++) {
            if (p[i].at == current_time && p[i].remt > 0 && p[i].ct == 0) {
                int found = 0;
                for(int k=0; k<qc; k++) {
                    if(readyQ[k] == i) found = 1;
                }
                if(!found) {
                    enqueue(i);
                }
            }
        }
        if (rp != -1 && qc > 0) {
            int best_idx_in_q = get_highest_priority_process(p);
            int best_pid_in_q = readyQ[best_idx_in_q];
            if (p[best_pid_in_q].qlvl < p[rp].qlvl) {
                enqueue(rp);
                rp = -1;
                sc = 0;
            }
        }
        if (rp == -1) {
            if (qc > 0) {
                int best_idx = get_highest_priority_process(p);
                rp = readyQ[best_idx];
                remove_from_queue(best_idx);
                sc = 0; 
            }
        } 
        if (rp != -1) {
            p[rp].remt--;
            sc++;
            if (p[rp].remt == 0) {
                p[rp].ct = current_time + 1;
                p[rp].tat = p[rp].ct - p[rp].at;
                p[rp].wt = p[rp].tat - p[rp].bt;
                printf("Time %d: Process %d completed (Queue %d)\n", current_time + 1, p[rp].pid, p[rp].qlvl);
                completed++;
                rp = -1;
                sc = 0;
            } 
            else if (sc == time_quantum[p[rp].qlvl]) {
                if (p[rp].qlvl < 2) {
                    p[rp].qlvl++;
                }
                enqueue(rp);
                printf("Time %d: Process %d demoted to Queue %d\n", current_time + 1, p[rp].pid, p[rp].qlvl);
                rp = -1;
                sc = 0;
            }
        }

        current_time++;
    }
    printf("\nResults\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");
    float total_wt = 0, total_tat = 0;
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tat);
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }
    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}



//for the sample io, inputs given
//number of processes:4
//p1: arrival time=0, burst time=4
//p2: arrival time=3, burst time=6
//p3: arrival time=5, burst time=8
//p4: arrival time=6, burst time=9
