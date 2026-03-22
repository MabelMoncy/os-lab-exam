#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 9999

struct data {
    char s1[50];
    char s2[50];
    char s3[50];
    char result[200];
};

void flipCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper(str[i]))
            str[i] = tolower(str[i]);
        else if (islower(str[i]))
            str[i] = toupper(str[i]);
    }
}

int main() {
    int shmid;
    struct data *d;

    shmid = shmget(SHMKEY, sizeof(struct data), IPC_CREAT | 0666);
    d = (struct data *) shmat(shmid, NULL, 0);

    printf("Enter first string: ");
    scanf("%s", d->s1);

    printf("Enter second string: ");
    scanf("%s", d->s2);

    printf("Enter third string: ");
    scanf("%s", d->s3);

    sleep(20); // wait for process2

    flipCase(d->result);

    printf("Final Output: %s\n", d->result);

    shmdt(d);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}