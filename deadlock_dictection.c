#include <stdio.h>

int main() {
    int n = 3; // Number of processes
    int m = 2; // Number of resources

    // Allocation Matrix
    int allocation[3][2] = {
        {1, 0},
        {0, 1},
        {1, 1}
    };

    // Maximum Matrix
    int max[3][2] = {
        {1, 1},
        {1, 1},
        {2, 2}
    };

    // Available Resources
    int available[2] = {0, 0};

    int need[3][2];
    int finish[3] = {0};
    int work[2];
    int safeSeq[3];
    int count = 0;

    // Calculate Need Matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initialize Work = Available
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    // Safety Algorithm (Detection Phase)
    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {

                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                // If process can be executed
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        // No process found → stop
        if (!found) {
            break;
        }
    }

    // Deadlock Detection Result
    if (count == n) {
        printf("System is in SAFE state\nSafe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safeSeq[i]);
        }
        printf("\n");
    } else {
        printf("System is in DEADLOCK (UNSAFE STATE)\nDeadlocked processes: ");
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                printf("P%d ", i);
            }
        }
        printf("\n");
    }

    return 0;
}