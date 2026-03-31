#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CYLINDERS 5000
#define N 10

// ----------- Sort Function -----------
void sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}

// ----------- SSTF -----------
int sstf(int req[], int n, int head) {
    int visited[N] = {0};
    int total = 0, cur = head;

    for (int s = 0; s < n; s++) {
        int min = 1000000, idx = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int d = abs(cur - req[i]);
                if (d < min) {
                    min = d;
                    idx = i;
                }
            }
        }

        visited[idx] = 1;
        total += min;
        cur = req[idx];
    }

    return total;
}

// ----------- LOOK (Right first) -----------
int look(int req[], int n, int head) {
    int a[N];
    for (int i = 0; i < n; i++) a[i] = req[i];

    sort(a, n);

    int total = 0, cur = head;

    // Move right
    for (int i = 0; i < n; i++) {
        if (a[i] >= head) {
            total += abs(cur - a[i]);
            cur = a[i];
        }
    }

    // Reverse direction
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] < head) {
            total += abs(cur - a[i]);
            cur = a[i];
        }
    }

    return total;
}

// ----------- C-SCAN (Right first) -----------
int cscan(int req[], int n, int head) {
    int a[N];
    for (int i = 0; i < n; i++) a[i] = req[i];

    sort(a, n);

    int total = 0, cur = head;

    // Move right
    for (int i = 0; i < n; i++) {
        if (a[i] >= head) {
            total += abs(cur - a[i]);
            cur = a[i];
        }
    }

    // Go to end
    total += abs(cur - (CYLINDERS - 1));
    cur = CYLINDERS - 1;

    // Jump to start
    total += abs(cur - 0);
    cur = 0;

    // Continue servicing
    for (int i = 0; i < n; i++) {
        if (a[i] < head) {
            total += abs(cur - a[i]);
            cur = a[i];
        }
    }

    return total;
}

// ----------- MAIN -----------
int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <initial_head_position>\n", argv[0]);
        return 1;
    }

    int head = atoi(argv[1]);

    if (head < 0 || head >= CYLINDERS) {
        printf("Head position must be between 0 and 4999\n");
        return 1;
    }

    int req[N];

    srand(time(NULL));

    // Generate random requests
    for (int i = 0; i < N; i++) {
        req[i] = rand() % CYLINDERS;
    }

    printf("\nDisk Cylinders: 0 - 4999\n");
    printf("Initial Head Position: %d\n", head);

    printf("\nGenerated Requests:\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", req[i]);
    }
    printf("\n");

    int sstf_m = sstf(req, N, head);
    int look_m = look(req, N, head);
    int cscan_m = cscan(req, N, head);

    printf("\n=====================================\n");
    printf("Algorithm\tTotal Head Movement\n");
    printf("-------------------------------------\n");
    printf("SSTF\t\t%d\n", sstf_m);
    printf("LOOK\t\t%d\n", look_m);
    printf("C-SCAN\t\t%d\n", cscan_m);
    printf("=====================================\n");

    return 0;
}