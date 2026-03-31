#include <stdio.h>

int main() {
    int n = 5; // Number of processes
    int m = 3; // Number of resources

    // Allocation Matrix
    int alloc[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Maximum Matrix
    int max[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Available Resources
    int avail[3] = {3, 3, 2};

    int need[5][3];
    int finish[5] = {0};
    int safeSeq[5];
    int work[3];

    // Initialize work = available
    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    // Calculate Need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int count = 0;

    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {

                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                // If all needs satisfied
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        // If no process found → unsafe
        if (!found) {
            printf("System is in UNSAFE state\n");
            return 0;
        }
    }

    // Safe state
    printf("System is in SAFE state\nSafe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }

    return 0;
}