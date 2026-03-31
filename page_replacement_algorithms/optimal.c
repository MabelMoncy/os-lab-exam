#include <stdio.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

int frames[MAX_FRAMES];
int faults = 0;

void initializeFrames(int f) {
    for (int i = 0; i < f; i++)
        frames[i] = -1;
}

int findPage(int page, int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == page)
            return i;
    }
    return -1;
}

int findOptimal(int pages[], int n, int index, int f) {
    int farthest = index, pos = -1;

    for (int i = 0; i < f; i++) {
        int j;
        for (j = index + 1; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }

        // Not used in future
        if (j == n)
            return i;
    }

    if (pos == -1)
        return 0;

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
        int pos = findPage(pages[i], f);

        if (pos != -1) {
            display(pages[i], f, 1);
        } else {
            int replaceIndex = -1;

            // Check empty frame
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            if (replaceIndex == -1)
                replaceIndex = findOptimal(pages, n, i, f);

            frames[replaceIndex] = pages[i];
            faults++;

            display(pages[i], f, 0);
        }
    }

    printf("\nTotal Page Faults = %d\n", faults);
    return 0;
}