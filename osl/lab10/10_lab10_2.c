/*Write a C/C++ program to simulate LRU Page Replacement. Frame allocation must be done
as per user input and dynamic allocation for all data structures. Find the total number of page
faults and hit ratio for the algorithm.
*/

#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int page_number; int last_used_time;
} Frame;
int main(){
    int num_frames, num_pages;
    int page_faults=0; int page_hits=0;
    int time_counter=1;
    printf("Enter the total number of frames:"); scanf("%d", &num_frames);
    printf("Enter the total number of pages in the reference string:"); scanf("%d", &num_pages);
    int *page_reference_string=(int *)malloc(num_pages*sizeof(int));
    Frame *frames =(Frame *)malloc(num_frames * sizeof(Frame));
    if (page_reference_string == NULL || frames == NULL) {
        printf("Memory allocation failed!\n");return 1;}
    for (int i = 0; i < num_frames; i++) {
        frames[i].page_number = -1;
        frames[i].last_used_time = 0;}
    printf("Enter the page reference string (space-separated):");
    for (int i=0; i<num_pages;i++){
        scanf("%d",&page_reference_string[i]);
    }
    printf("\nLRU PAGE REPLACEMENT SIMULATION\n");
    printf("Page\tFrames\t\t\tFault/Hit\n");
    printf("______________________________________________________\n");
    for (int i = 0; i < num_pages; i++) {
        int current_page = page_reference_string[i];
        int hit = 0;int lru_index = 0;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j].page_number == current_page) {
                hit = 1;page_hits++;
                frames[j].last_used_time = time_counter;
                break;
            }
        }
    if (!hit) {
            page_faults++;
            int empty_slot_found = 0;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j].page_number == -1) {
                    frames[j].page_number = current_page;
                    frames[j].last_used_time = time_counter;
                    empty_slot_found = 1;
                    break;
                }
            }
    if (!empty_slot_found) {
                int min_time = frames[0].last_used_time;
                lru_index = 0;
                for (int j = 1; j < num_frames; j++) {
                    if (frames[j].last_used_time < min_time) {
                        min_time = frames[j].last_used_time;
                        lru_index = j;
                    }
                }
                frames[lru_index].page_number = current_page;
                frames[lru_index].last_used_time = time_counter;
            }
        }
    time_counter++;
    printf("%d\t", current_page);
        for (int j = 0; j < num_frames; j++) {
            if (frames[j].page_number != -1) {
                printf("%d ", frames[j].page_number);} 
            else {printf("- ");}}
        if (hit) {printf("\t\tHIT\n");} 
        else {printf("\t\tFAULT\n");}}
    double hit_ratio = (double)page_hits / num_pages;
    double fault_ratio = (double)page_faults / num_pages;
    printf("_____________________________________________________________________\n");
    printf("Total Page Faults : %d\n", page_faults);
    printf("Total Page Hits   : %d\n", page_hits);
    printf("Hit Ratio         : %.4f (%.2f%%)\n", hit_ratio, hit_ratio * 100);
    printf("Fault Ratio       : %.4f (%.2f%%)\n", fault_ratio, fault_ratio * 100);
    free(page_reference_string);
    free(frames);
    return 0;
}