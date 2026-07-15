#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msgType;
    int msgTxt;
} msg;

int main() {
    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666);
    if (msgid == -1) { perror("msgget failed (Receiver might not be running)"); exit(1); }
    printf("Process A (Sender): Enter a number: ");
    scanf("%d", &msg.msgTxt);
    msg.msgType = 1;
    msgsnd(msgid, &msg, sizeof(msg), 0);
    printf("Process A: Sent %d.\n", msg.msgTxt);

    return 0;
}