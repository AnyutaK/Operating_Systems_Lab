#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_FILE "/tmp/my_fifo"
#define count 4

int main() {
    int fd;
    int arr[count];
    fd = open(FIFO_FILE, O_WRONLY); 
    printf("Producer: Enter %d integers:\n", count);
    for(int i = 0; i < count; i++) {
        scanf("%d", &arr[i]);}
    write(fd, arr, sizeof(arr));
    printf("Producer: Data written to FIFO.\n");
    close(fd);
    return 0;
}