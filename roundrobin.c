#include <stdio.h>

struct Process {
    int pid;
    int at;   // Arrival Time
    int bt;   // Burst Time
    int rt;   // Remaining Time
    int ct;   // Completion Time
    int tat;  // Turnaround Time
    int wt;   // Waiting Time
};

int main() {
    int n, tq;
    int time = 0, completed = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time of P%d: ", i + 1);
        scanf("%d", &p[i].at);

        printf("Enter Burst Time of P%d: ", i + 1);
        scanf("%d", &p[i].bt);

        p[i].rt = p[i].bt; // Initialize remaining time
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    int queue[100], front = 0, rear = 0;
    int inQueue[n];

    // Initialize inQueue array
    for (int i = 0; i < n; i++) {
        inQueue[i] = 0;
    }

    // Add processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].at == 0) {
            queue[rear++] = i;
            inQueue[i] = 1;
        }
    }

    while (completed != n) {

        // If queue is empty → CPU idle
        if (front == rear) {
            time++;

            // Add newly arrived processes
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && !inQueue[i]) {
                    queue[rear++] = i;
                    inQueue[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];

        // Execute process
        int execTime = (p[idx].rt < tq) ? p[idx].rt : tq;
        time += execTime;
        p[idx].rt -= execTime;

        // Add newly arrived processes during execution
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !inQueue[i]) {
                queue[rear++] = i;
                inQueue[i] = 1;
            }
        }

        // If process not finished → requeue
        if (p[idx].rt > 0) {
            queue[rear++] = idx;
        } else {
            p[idx].ct = time;
            completed++;
        }
    }

    // Calculate TAT and WT
    float totalWT = 0;

    printf("\n--- Round Robin Scheduling Result ---\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        totalWT += p[i].wt;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);

    return 0;
}