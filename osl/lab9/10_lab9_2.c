/*
Assuming a page size of 32 bytes and there are total of 8 such pages totaling 256 bytes. Write
a C program to simulate this memory mapping. The program should read the logical memory
address and display the page number and page offset in decimal. How many bytes do you
need to represent the address in this scenario? Display the page number and offset to
reference the following logical addresses.
(i) 204 byte
(ii) 56 byte
*/
#include <stdio.h>
void calculateAddressMapping(int logicalAddress, int pageSize, int *pageNumber, int *offset) {
    *pageNumber = logicalAddress / pageSize;
    *offset = logicalAddress % pageSize;
}
void displayMapping(int logicalAddress, int pageNumber, int offset) {
    printf("\nMAPPING RESULT\n");
    printf("Logical Address : %d byte\n", logicalAddress);
    printf("Page Number     : %d\n", pageNumber);
    printf("Page Offset     : %d\n", offset);
}
int main() {
    int pageSize = 32;
    int totalPages = 8;
    int totalMemory = pageSize * totalPages; 
    int logicalAddress;
    int pageNumber, offset;
    int bitsNeeded, bytesNeeded;
    bitsNeeded = 0;
    int temp = totalMemory;
    while (temp > 1) {
        temp >>= 1;
        bitsNeeded++;
    }
    bytesNeeded = bitsNeeded / 8;

    printf("       MEMORY MAPPING SIMULATION\n");
    printf("==================================================\n");
    printf("Total Memory   : %d bytes\n", totalMemory);
    printf("Page Size      : %d bytes\n", pageSize);
    printf("Address Bus    : %d bits (%d byte(s))\n", bitsNeeded, bytesNeeded);
    printf("==================================================\n\n");
    printf("Enter a logical address (in decimal, 0-255): ");
    scanf("%d", &logicalAddress);
    if (logicalAddress < 0 || logicalAddress >= totalMemory) {
        printf("\nError: Address %d is invalid.\n", logicalAddress);
        printf("Please enter an address between 0 and %d.\n", totalMemory - 1);
        return 1;
    }
    calculateAddressMapping(logicalAddress, pageSize, &pageNumber, &offset);
    displayMapping(logicalAddress, pageNumber, offset);
    return 0;
}