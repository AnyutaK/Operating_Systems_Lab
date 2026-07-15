#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 20

struct Process {
    int pid;
    int at;
    int bt;
    int priority;
    int ct;
    int tat;
    int wt;
    int rt;
    int initial_bt;
};

struct Process p[MAX];
struct Process og[MAX];
int n;

void inputProcesses();
void resetProcesses();
void sortByID();
void printResults();
void drawGanttChart(int gp[], int gt[], int count);
void fcfs();
void srtf();
void roundRobin();
void priorityNonPreemptive();

int min(int a, int b) {
    return (a < b) ? a : b;
}

void inputProcesses() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nProcess P%d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);

        printf("Burst Time: ");
        scanf("%d", &p[i].bt);

        printf("Priority: ");
        scanf("%d", &p[i].priority);

        p[i].initial_bt = p[i].bt;
        p[i].rt = p[i].bt;
        og[i] = p[i];
    }
}

void resetProcesses() {
    for(int i = 0; i < n; i++) {
        p[i] = og[i];
        p[i].rt = p[i].initial_bt;
        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
    }
}

void sortByID() {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].pid > p[j + 1].pid) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void printResults() {
    float total_wt = 0, total_tat = 0;

    sortByID();

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].initial_bt;

        total_wt += p[i].wt;
        total_tat += p[i].tat;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].initial_bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt/n);
    printf("Average Turnaround Time: %.2f\n", total_tat/n);
}

void drawGanttChart(int gp[], int gt[], int count) {
    printf("\nGantt Chart:\n");

    for(int i = 0; i < count; i++)
        printf("___________________________________________");
    printf("\n|");

    for(int i = 0; i < count; i++) {
        if(gp[i] == -1)
            printf(" IDLE |");
        else
            printf("  P%d  |", gp[i]);
    }

    printf("\n");

    for(int i = 0; i < count; i++)
        printf("____________________________________________");

    printf("\n0");
    for(int i = 0; i < count; i++)
        printf("%7d", gt[i]);

    printf("\n");
}

void fcfs() {
    resetProcesses();

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int current_time = 0;
    int gp[MAX], gt[MAX];
    int g_count = 0;

    for(int i = 0; i < n; i++) {
        if(current_time < p[i].at) {
            gp[g_count] = -1;
            gt[g_count++] = p[i].at;
            current_time = p[i].at;
        }

        gp[g_count] = p[i].pid;
        current_time += p[i].bt;
        p[i].ct = current_time;
        gt[g_count++] = current_time;
    }

    drawGanttChart(gp, gt, g_count);
    printResults();
}

void srtf() {
    resetProcesses();

    int complete = 0, current_time = 0;
    int gp[200], gt[200], g_count = 0;
    int prev = -1;

    while(complete < n) {
        int shortest = -1;
        int min_rt = INT_MAX;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= current_time && p[i].rt > 0 && p[i].rt < min_rt) {
                min_rt = p[i].rt;
                shortest = i;
            }
        }

        if(shortest == -1) {
            current_time++;
            continue;
        }

        if(prev != p[shortest].pid) {
            gp[g_count] = p[shortest].pid;
            gt[g_count++] = current_time;
            prev = p[shortest].pid;
        }

        p[shortest].rt--;
        current_time++;

        if(p[shortest].rt == 0) {
            p[shortest].ct = current_time;
            complete++;
        }
    }

    gt[g_count - 1] = current_time;

    drawGanttChart(gp, gt, g_count);
    printResults();
}

void roundRobin() {
    resetProcesses();

    int quantum;
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int queue[200], front = 0, rear = 0;
    int gp[200], gt[200], g_count = 0;
    int current_time = 0, complete = 0;
    int in_queue[MAX] = {0};

    while(complete < n) {
        for(int i = 0; i < n; i++)
            if(p[i].at <= current_time && p[i].rt > 0 && !in_queue[i]) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }

        if(front == rear) {
            current_time++;
            continue;
        }

        int idx = queue[front++];
        in_queue[idx] = 0;

        gp[g_count] = p[idx].pid;

        int exec = min(quantum, p[idx].rt);
        current_time += exec;
        p[idx].rt -= exec;
        gt[g_count++] = current_time;

        for(int i = 0; i < n; i++)
            if(p[i].at <= current_time && p[i].rt > 0 && !in_queue[i]) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }

        if(p[idx].rt > 0) {
            queue[rear++] = idx;
            in_queue[idx] = 1;
        } else {
            p[idx].ct = current_time;
            complete++;
        }
    }

    drawGanttChart(gp, gt, g_count);
    printResults();
}

void priorityNonPreemptive() {
    resetProcesses();

    int current_time = 0, complete = 0;
    int done[MAX] = {0};
    int gp[MAX], gt[MAX], g_count = 0;

    while(complete < n) {
        int idx = -1;
        int highest = -1;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= current_time && !done[i]) {
                if(p[i].priority > highest) {
                    highest = p[i].priority;
                    idx = i;
                }
            }
        }

        if(idx == -1) {
            current_time++;
            continue;
        }

        gp[g_count] = p[idx].pid;
        current_time += p[idx].bt;
        p[idx].ct = current_time;
        gt[g_count++] = current_time;

        done[idx] = 1;
        complete++;
    }

    drawGanttChart(gp, gt, g_count);
    printResults();
}

int main() {
    int choice;

    inputProcesses();

    do {
        printf("\n1.FCFS\n");
        printf("2. SRTF\n");
        printf("3. Round Robin\n");
        printf("4. Non-Preemptive Priority\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: fcfs(); break;
            case 2: srtf(); break;
            case 3: roundRobin(); break;
            case 4: priorityNonPreemptive(); break;
            case 5: printf("Exiting\n"); break;
            default: printf("Invalid choice\n");
        }

    } while(choice != 5);

    return 0;
}


//gantt chart for output
// process,arrival time, burst time, priority
//P1,0,60,3
//P2,3,30,2
//P3,4,40,1
//P4,9,10,4