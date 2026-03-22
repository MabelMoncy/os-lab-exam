#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSGKEY 1234

struct msg {
    long type;
    char text[100];
};

int main() {
    struct msg m1, m2;
    int qid;

    qid = msgget(MSGKEY, IPC_CREAT | 0666);

    printf("Enter a string: ");
    scanf("%s", m1.text);

    m1.type = 1;
    msgsnd(qid, &m1, sizeof(m1.text), 0);

    msgrcv(qid, &m2, sizeof(m2.text), 2, 0);

    printf("Reversed string: %s\n", m2.text);

    if (strcmp(m1.text, m2.text) == 0)
        printf("Palindrome\n");
    else
        printf("Not Palindrome\n");

    msgctl(qid, IPC_RMID, NULL);

    return 0;
}