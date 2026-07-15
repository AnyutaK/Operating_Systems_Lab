#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msg_buffer {
    long msgType;
    int msgTxt;
} msg;

int isPalindrome(int n) {
    int og = n, rev = 0, rem;
    while (n != 0) {
        rem = n % 10;
        rev = rev * 10 + rem;
        n /= 10;
    }
    return og == rev;
}

int main() {
    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) { perror("msgget failed"); exit(1); }
    printf("Process B (Receiver): Waiting for message...\n");
    msgrcv(msgid, &msg, sizeof(msg), 1, 0);
    printf("Process B: Received %d.\n", msg.msgTxt);
    if (isPalindrome(msg.msgTxt))
        printf("Process B: %d is a Palindrome.\n", msg.msgTxt);
    else
        printf("Process B: %d is NOT a Palindrome.\n", msg.msgTxt);
    msgctl(msgid, IPC_RMID, NULL);
    printf("Process B: Queue deleted. Exiting.\n");

    return 0;
}