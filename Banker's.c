#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int processes, resources;
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    bool finished[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];
    int i, j, count = 0;

    // Input
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < processes; i++)
        for (j = 0; j < resources; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Max Matrix:\n");
    for (i = 0; i < processes; i++)
        for (j = 0; j < resources; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (i = 0; i < resources; i++)
        scanf("%d", &available[i]);

    // Calculate Need Matrix
    for (i = 0; i < processes; i++)
        for (j = 0; j < resources; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // New request
    int reqPID, request[MAX_RESOURCES];
    printf("\nEnter the process ID making a request (0 to %d): ", processes - 1);
    scanf("%d", &reqPID);
    printf("Enter resource request for P%d: ", reqPID);
    for (i = 0; i < resources; i++)
        scanf("%d", &request[i]);

    // Check request validity
    bool valid = true;
    for (i = 0; i < resources; i++) {
        if (request[i] > need[reqPID][i]) {
            valid = false;
            break;
        }
        if (request[i] > available[i]) {
            valid = false;
            break;
        }
    }

    if (!valid) {
        printf("\nRequest cannot be granted (exceeds need or availability).\n");
        return 1;
    }

    // Pretend to allocate
    for (i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[reqPID][i] += request[i];
        need[reqPID][i] -= request[i];
    }

    // Begin Banker's Algorithm
    printf("\nProcess Execution:\n");
    while (count < processes) {
        bool found = false;
        for (i = 0; i < processes; i++) {
            if (!finished[i]) {
                bool canAllocate = true;
                for (j = 0; j < resources; j++) {
                    if (need[i][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (j = 0; j < resources; j++)
                        available[j] += allocation[i][j];

                    safeSequence[count++] = i;
                    finished[i] = true;

                    printf("P%d executed (Available: ", i);
                    for (j = 0; j < resources; j++)
                        printf("%d ", available[j]);
                    printf(")\n");

                    found = true;
                }
            }
        }

        if (!found) {
            printf("\nSystem is NOT in a safe state after request. Request denied.\n");
            return 1;
        }
    }

    // Final State
    printf("\nFinal State After Execution:\n");
    printf("Process\tAllocation\tMax\t\tNeed\n");
    for (i = 0; i < processes; i++) {
        printf("P%d\t", i);
        for (j = 0; j < resources; j++)
            printf("%d ", allocation[i][j]);
        printf("\t\t");
        for (j = 0; j < resources; j++)
            printf("%d ", max[i][j]);
        printf("\t\t");
        for (j = 0; j < resources; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    printf("\nSafe Sequence: ");
    for (i = 0; i < processes; i++) {
        printf("P%d", safeSequence[i]);
        if (i < processes - 1) printf(" -> ");
    }

    printf("\n\nFinal Available Resources: ");
    for (i = 0; i < resources; i++)
        printf("%d ", available[i]);
    printf("\n");

    return 0;
}
