/* Write a C/C++ program to simulate page replacement algorithms: FIFO and
optimal. Frame allocation has to be done as per user input and use dynamic allocation
for all data structures.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int findOptimalVictim(int *pages, int numPages, int *frames, int numFrames, int currentIndex) {
    int farthest = -1;
    int victimIndex = 0;

    for (int i = 0; i < numFrames; i++) {
        int j;
        for (j = currentIndex + 1; j < numPages; j++) {
            if (frames[i] == pages[j]) {
                break;
            }
        }
        if (j == numPages) {
            return i;
        }
         if (j > farthest) {
            farthest = j;
            victimIndex = i;
        }
    }
    return victimIndex;
}
int simulateFIFO(int *pages, int numPages, int numFrames) {
    int *frames = (int *)malloc(numFrames * sizeof(int));
    if (!frames) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < numFrames; i++) frames[i] = -1;
    int front = 0;          
    int pageFaults = 0;
    int framesUsed = 0;     
    printf("\n__________");
    for (int i = 0; i < numFrames; i++) printf("__________+");
    printf("______________\n");
    printf("| Page |");
    for (int i = 0; i < numFrames; i++) printf(" Frame %d |", i);
    printf("   Status    |\n");
    printf("________");
    for (int i = 0; i < numFrames; i++) printf("__________");
    printf("______________\n");
    for (int i = 0; i < numPages; i++) {
        bool hit = false;
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                hit = true;
                break;
            }
        }
        printf("|  %2d  |", pages[i]);
        if (!hit) {
            if (framesUsed < numFrames) {
                frames[framesUsed++] = pages[i];
            } else {
                frames[front] = pages[i];
                front = (front + 1) % numFrames; 
            }
            pageFaults++;
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] != -1) printf("    %2d   |", frames[j]);
                else printf("    -    |");
            }
            printf(" PAGE FAULT  |\n");
        } else {
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] != -1) printf("    %2d   |", frames[j]);
                else printf("    -    |");
            }
            printf("  PAGE HIT   |\n");
        }
    }
    printf("________");
    for (int i = 0; i < numFrames; i++) printf("__________");
    printf("______________\n");
    printf("=> Total FIFO Page Faults: %d\n", pageFaults);
    free(frames); 
    return pageFaults;
}
int simulateOptimal(int *pages, int numPages, int numFrames) {
    int *frames = (int *)malloc(numFrames * sizeof(int));
    if (!frames) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < numFrames; i++) frames[i] = -1;
    int pageFaults = 0;
    int framesUsed = 0;
    printf("\n+_______");
    for (int i = 0; i < numFrames; i++) printf("___________");
    printf("______________\n");
    printf("| Page |");
    for (int i = 0; i < numFrames; i++) printf(" Frame %d |", i);
    printf("   Status    |\n");
    printf("________");
    for (int i = 0; i < numFrames; i++) printf("___________");
    printf("_______________\n");
    for (int i = 0; i < numPages; i++) {
        bool hit = false;
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == pages[i]) {
                hit = true;
                break;
            }
        }
        printf("|  %2d  |", pages[i]);
        if (!hit) {
            if (framesUsed < numFrames) {
                frames[framesUsed++] = pages[i];
            } else {
                int victim = findOptimalVictim(pages, numPages, frames, numFrames, i);
                frames[victim] = pages[i];
            }
            pageFaults++;

            for (int j = 0; j < numFrames; j++) {
                if (frames[j] != -1) printf("    %2d   |", frames[j]);
                else printf("    -    |");
            }
            printf(" PAGE FAULT  |\n");
        } else {
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] != -1) printf("    %2d   |", frames[j]);
                else printf("    -    |");
            }
            printf("  PAGE HIT   |\n");
        }
    }
    printf("____________");
    for (int i = 0; i < numFrames; i++) printf("__________");
    printf("______________\n");
    printf("=> Total Optimal Page Faults: %d\n", pageFaults);
    free(frames); 
    return pageFaults;
}

int main() {
    int numPages, numFrames;
    int *pages = NULL;
    int choice;
    printf("Page Replacement Algorithm Simulation\n______________________________________________\n");
    printf("Enter total number of page references: ");
    scanf("%d", &numPages);
    pages = (int *)malloc(numPages * sizeof(int));
    if (!pages) {
        printf("Memory allocation failed for pages!\n");
        return 1;
    }
    printf("Enter the page reference string (space separated):\n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);
    printf("\nChoose Algorithm:\n1. FIFO\n2. Optimal\n3. Both (Compare)\nChoice: ");
    scanf("%d", &choice);
    int fifoFaults = 0, optimalFaults = 0;
    switch (choice) {
        case 1:
            fifoFaults = simulateFIFO(pages, numPages, numFrames);
            break;
        case 2:
            optimalFaults = simulateOptimal(pages, numPages, numFrames);
            break;
        case 3:
            fifoFaults = simulateFIFO(pages, numPages, numFrames);
            optimalFaults = simulateOptimal(pages, numPages, numFrames);
            printf("\nCOMPARISON SUMMARY\n");
            printf("Algorithm  | Page Faults\n");
            printf("__________________________\n");
            printf("FIFO       |     %2d      \n", fifoFaults);
            printf("Optimal    |     %2d      \n", optimalFaults);
            if (optimalFaults <= fifoFaults)
                printf("\n=> Optimal performed better (as expected theoretically).\n");
            else
                printf("\n=> Anomaly detected or invalid input sequence.\n");
            break;
        default:
            printf("Invalid choice!\n");
    }
    free(pages);

    return 0;
}


