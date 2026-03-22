#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 9999

struct data {
    char s1[50];
    char s2[50];
    char s3[50];
    char result[200];
};

int main() {
    int shmid;
    struct data *d;

    shmid = shmget(SHMKEY, sizeof(struct data), IPC_CREAT | 0666);
    d = (struct data *) shmat(shmid, NULL, 0);

    sprintf(d->result, "%s %s %s", d->s1, d->s2, d->s3);

    printf("Concatenation done\n");

    shmdt(d);

    return 0;
}