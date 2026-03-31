#include <stdio.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

int frames[MAX_FRAMES];
int time[MAX_FRAMES];
int counter = 0;
int faults = 0;

void initializeFrames(int f) {
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }
}

int findPage(int page, int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

int findLRU(int f) {
    int min = time[0], pos = 0;
    for (int i = 1; i < f; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

void display(int page, int f, int hit) {
    printf("%d\t", page);
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf("-\t");
        else
            printf("%d\t", frames[i]);
    }
    printf(hit ? "Hit\n" : "Fault\n");
}

int main() {
    int pages[MAX_PAGES];
    int n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    initializeFrames(f);

    printf("\nPage\t");
    for (int i = 0; i < f; i++)
        printf("F%d\t", i + 1);
    printf("Status\n");

    for (int i = 0; i < n; i++) {
        counter++;
        int pos = findPage(pages[i], f);

        if (pos != -1) {
            time[pos] = counter;
            display(pages[i], f, 1);
        } else {
            int replaceIndex;

            if (i < f)
                replaceIndex = i;
            else
                replaceIndex = findLRU(f);

            frames[replaceIndex] = pages[i];
            time[replaceIndex] = counter;
            faults++;

            display(pages[i], f, 0);
        }
    }

    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}