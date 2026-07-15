/*
Write a C/C++ program to simulate First-fit, Best-fit and Worst-fit strategies. Given memory
partitions of 100K, 500K, 200K, 300K, and 600K(in order), how would each of the First-fit,
Best-fit, and Worst-fit algorithms place processes of 212K, 417K, 112K, and 426K (in
order)? Which algorithm makes efficient use of memory?
*/

#include <stdio.h>
#include <string.h>
void firstFit(int blockSize[], int m, int processSize[], int n){
	int block[m];
	memcpy(block,blockSize,sizeof(block));
	printf("FIRST FIT ALLOCATION\n");
	printf("Prcoess Size\t | Book Allocated\n");
	for (int i=0; i<n;i++){
		int allocated = 0;
		for (int j=0; j<m;j++){
			if (block[j] >= processSize[i]){
				printf("%dK\t\t| Block %d (%dK)\n", processSize[i],j+1,blockSize[j]);
				block[j]-=processSize[i];
				allocated=1;
				break;
			}
		}
		if (!allocated){
			printf("%dK\t\t| Not Allocated\n", processSize[i]);
		}
	}
}
void bestFit(int blockSize[], int m, int processSize[], int n) {
    int block[m];
    memcpy(block, blockSize, sizeof(block));
    printf("\nBESTT FIT ALLOCATION\n");
    printf("Process Size\t| Block Allocated\n");
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;        
        for (int j = 0; j < m; j++) {
            if (block[j] >= processSize[i]) {
                if (bestIdx == -1) {
                    bestIdx = j;
                } else if (block[j] < block[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            printf("%dK\t\t| Block %d (%dK)\n", processSize[i], bestIdx + 1, blockSize[bestIdx]);
            block[bestIdx] -= processSize[i];
        } else {
            printf("%dK\t\t| Not Allocated\n", processSize[i]);
        }
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int block[m];
    memcpy(block, blockSize, sizeof(block));

    printf("\nWORST FIT ALLOCATION\n");
    printf("Process Size\t| Block Allocated\n");
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (block[j] >= processSize[i]) {
                if (worstIdx == -1) {
                    worstIdx = j;
                } else if (block[j] > block[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            printf("%dK\t\t| Block %d (%dK)\n", processSize[i], worstIdx + 1, blockSize[worstIdx]);
            block[worstIdx] -= processSize[i];
        } else {
            printf("%dK\t\t| Not Allocated\n", processSize[i]);
        }
    }
}

int main(){
	int blockSize[]={100,500,200,300,600};
	int processSize[]={212,417,112,426};
	int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);
    firstFit(blockSize, m, processSize, n);
    bestFit(blockSize, m, processSize, n);
    worstFit(blockSize, m, processSize, n);
    return 0;
}