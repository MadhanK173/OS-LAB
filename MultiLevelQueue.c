#include <stdio.h>

#define MAX_PROCESSES 100

struct Process {
    int pid;
    int arrival;
    int burst;
    int queueType;
    int completion;
    int turnaround;
    int waiting;
};

void multiLevelQueueScheduling(struct Process p[], int n) {
    struct Process readyQueue[MAX_PROCESSES];
    int queueCount = 0, time = 0;
    float totalTurnaround = 0, totalWaiting = 0;


    for (int i = 0; i < n; i++)
        readyQueue[queueCount++] = p[i];

    for (int i = 0; i < queueCount; i++) {
        if (time < readyQueue[i].arrival)
            time = readyQueue[i].arrival;
        readyQueue[i].completion = time + readyQueue[i].burst;
        readyQueue[i].turnaround = readyQueue[i].completion - readyQueue[i].arrival;
        readyQueue[i].waiting = readyQueue[i].turnaround - readyQueue[i].burst;
        totalTurnaround += readyQueue[i].turnaround;
        totalWaiting += readyQueue[i].waiting;
        time = readyQueue[i].completion;
    }

    printf("\nPID\tArrival\tBurst\tQueue\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < queueCount; i++) {
        if (readyQueue[i].queueType == 0)
            printf("%d\t%d\t%d\tSystem\t%d\t\t%d\t\t%d\n", readyQueue[i].pid, readyQueue[i].arrival, readyQueue[i].burst, readyQueue[i].completion, readyQueue[i].turnaround, readyQueue[i].waiting);
    }
    for (int i = 0; i < queueCount; i++) {
        if (readyQueue[i].queueType == 1)
            printf("%d\t%d\t%d\tUser\t%d\t\t%d\t\t%d\n", readyQueue[i].pid, readyQueue[i].arrival, readyQueue[i].burst, readyQueue[i].completion, readyQueue[i].turnaround, readyQueue[i].waiting);
    }

    printf("\nAverage Turnaround Time: %.2f", totalTurnaround / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWaiting / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[MAX_PROCESSES];
    printf("Enter PID, Arrival Time, Burst Time, Queue Type (0-System, 1-User):\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d %d %d", &p[i].pid, &p[i].arrival, &p[i].burst, &p[i].queueType);

    multiLevelQueueScheduling(p, n);
    return 0;
}
