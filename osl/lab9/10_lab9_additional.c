/*We have five segments numbered 0 through 4. The segments are stored in physical memory
as shown in the following Fig 10.3. Write a C program to create segment table. Write
methods for converting logical address to physical address. Compute the physical address
for the following.
(i) 53 byte of segment 2 (ii) 852 byte of segment 3 (iii) 1222 byte of segment 0
     Segment 0: Base 1400, Limit 1000 (2400 - 1400)
     Segment 1: Base 6300, Limit 400 (6700 - 6300)
     Segment 2: Base 4300, Limit 400 (4700 - 4300)
     Segment 3: Base 3200, Limit 1100 (4300 - 3200)
     Segment 4: Base 4700, Limit 1000 (5700 - 4700)

*/

#include <stdio.h>
#include <stdlib.h>
#define NUM_SEGMENTS 5
typedef struct {
    int segmentNumber;
    int base;   
    int limit;  
} SegmentTableEntry;
void createSegmentTable(SegmentTableEntry table[]) {
    // Segment 0: B 1400, L 2400 
    table[0].segmentNumber = 0;
    table[0].base = 1400;
    table[0].limit = 1000;

    // Segment 1: B 6300, L 6700 
    table[1].segmentNumber = 1;
    table[1].base = 6300;
    table[1].limit = 400;

    // Segment 2: B 4300, L 4700 
    table[2].segmentNumber = 2;
    table[2].base = 4300;
    table[2].limit = 400;

    // Segment 3: B 3200, L 4300 
    table[3].segmentNumber = 3;
    table[3].base = 3200;
    table[3].limit = 1100;

    // Segment 4: B 4700, L 5700 
    table[4].segmentNumber = 4;
    table[4].base = 4700;
    table[4].limit = 1000;
}

void calculatePhysicalAddress(SegmentTableEntry table[], int segNum, int offset) {
    printf("Input: Segment %d, Offset %d\n", segNum, offset);
    if (segNum < 0 || segNum >= NUM_SEGMENTS) {
        printf("Error: Invalid Segment Number.\n\n");
        return;
    }
    if (offset >= table[segNum].limit) {
        printf("Error: Segmentation Fault (Offset %d >= Limit %d).\n\n", offset, table[segNum].limit);
        return;
    }
    int physicalAddress = table[segNum].base + offset;
    printf("Result: Physical Address = Base(%d) + Offset(%d) = %d\n\n", table[segNum].base, offset, physicalAddress);
}
void displayTable(SegmentTableEntry table[]) {
    printf("GENERATED SEGMENT TABLE\n");
    printf("Seg No.\tBase\tLimit\n");
    printf("__________________________________\n");
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        printf("%d\t%d\t%d\n", table[i].segmentNumber, table[i].base, table[i].limit);
    }
    printf("================================\n\n");
}

int main() {
    SegmentTableEntry table[NUM_SEGMENTS];
    createSegmentTable(table);
    displayTable(table);    
    printf("(i) 53 byte of segment 2:\n");
    calculatePhysicalAddress(table, 2, 53);
    printf("(ii) 852 byte of segment 3:\n");
    calculatePhysicalAddress(table, 3, 852);
    printf("(iii) 1222 byte of segment 0:\n");
    calculatePhysicalAddress(table, 0, 1222);
    return 0;
}