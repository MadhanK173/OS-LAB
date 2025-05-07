#include <stdio.h>

#define MAX 100

// Function to check if page is in frames
int isInFrame(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

// FIFO Page Replacement
void FIFO(int pages[], int n, int capacity) {
    int frames[MAX], front = 0, count = 0, pageFaults = 0;
    for (int i = 0; i < capacity; i++) frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        if (!isInFrame(frames, capacity, pages[i])) {
            frames[front] = pages[i];
            front = (front + 1) % capacity;
            pageFaults++;
        }
        printf("Page %d: ", pages[i]);
        for (int j = 0; j < capacity; j++)
            if (frames[j] != -1)
                printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

// LRU Page Replacement
void LRU(int pages[], int n, int capacity) {
    int frames[MAX], time[MAX], counter = 0, pageFaults = 0;
    for (int i = 0; i < capacity; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == pages[i]) {
                time[j] = counter++;
                found = 1;
                break;
            }
        }

        if (!found) {
            int lruIndex = 0;
            for (int j = 1; j < capacity; j++) {
                if (time[j] < time[lruIndex])
                    lruIndex = j;
            }
            frames[lruIndex] = pages[i];
            time[lruIndex] = counter++;
            pageFaults++;
        }

        printf("Page %d: ", pages[i]);
        for (int j = 0; j < capacity; j++)
            if (frames[j] != -1)
                printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

// Optimal Page Replacement
void Optimal(int pages[], int n, int capacity) {
    int frames[MAX], pageFaults = 0;
    for (int i = 0; i < capacity; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        if (!isInFrame(frames, capacity, pages[i])) {
            int replaceIndex = -1, farthest = i + 1;
            for (int j = 0; j < capacity; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k])
                        break;
                }
                if (k > farthest) {
                    farthest = k;
                    replaceIndex = j;
                }
                if (k == n) {  // not found again
                    replaceIndex = j;
                    break;
                }
            }
            if (replaceIndex == -1) replaceIndex = 0;
            frames[replaceIndex] = pages[i];
            pageFaults++;
        }

        printf("Page %d: ", pages[i]);
        for (int j = 0; j < capacity; j++)
            if (frames[j] != -1)
                printf("%d ", frames[j]);
        printf("\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

// Main Function
int main() {
    int pages[MAX], n, capacity;

    printf("Enter number of page references: ");
    scanf("%d", &n);
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    FIFO(pages, n, capacity);
    LRU(pages, n, capacity);
    Optimal(pages, n, capacity);

    return 0;
}
