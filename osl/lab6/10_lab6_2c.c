#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_FILE "/tmp/my_fifo"
#define count 4

int main() {
    int fd;
    int read_buff[count];
    mkfifo(FIFO_FILE, 0666);
    printf("Consumer: Waiting for Producer to write data...\n");
    fd = open(FIFO_FILE, O_RDONLY);
    read(fd, read_buff, sizeof(read_buff));
    printf("Consumer: Received data: ");
    for(int i = 0; i < count; i++) {
        printf("%d ", read_buff[i]);
    }
    printf("\n");
    close(fd);
    return 0;
}