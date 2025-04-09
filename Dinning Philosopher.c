#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 5

sem_t forks[MAX_PHILOSOPHERS];
pthread_mutex_t lock;
int hungry_philosophers[MAX_PHILOSOPHERS] = {0};
int num_hungry = 0;
int choice;

void* philosopher(void* num) {
    int id = *(int*)num;
    while (1) {
        if (hungry_philosophers[id]) {
            sem_wait(&forks[id]);
            sem_wait(&forks[(id + 1) % MAX_PHILOSOPHERS]);
            printf("P %d is granted to eat\n", id + 1);
            sleep(2);
            printf("P %d has finished eating\n", id + 1);
            hungry_philosophers[id] = 0;
            sem_post(&forks[id]);
            sem_post(&forks[(id + 1) % MAX_PHILOSOPHERS]);
            for (int i = 0; i < MAX_PHILOSOPHERS; i++) {
                if (hungry_philosophers[i]) {
                    printf("P %d is waiting\n", i + 1);
                }
            }
            pthread_exit(NULL);
        }
        sleep(1);
    }
}

int main() {
    int num_philosophers;
    printf("Enter the total number of philosophers: ");
    scanf("%d", &num_philosophers);

    printf("How many are hungry: ");
    scanf("%d", &num_hungry);
    int hungry_list[num_hungry];
    for (int i = 0; i < num_hungry; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, num_philosophers);
        scanf("%d", &hungry_list[i]);
        hungry_philosophers[hungry_list[i] - 1] = 1;
    }

    for (int i = 0; i < num_philosophers; i++) {
        sem_init(&forks[i], 0, 1);
    }

    printf("\n1. One can eat at a time\n2. Two can eat at a time\n3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    pthread_t philosophers[num_philosophers];
    int ids[num_philosophers];

    printf("Allow one philosopher to eat at any time\n");
    for (int i = 0; i < num_hungry; i++) {
        printf("P %d is waiting\n", hungry_list[i]);
    }

    for (int i = 0; i < num_hungry; i++) {
        ids[hungry_list[i] - 1] = hungry_list[i] - 1;
        pthread_create(&philosophers[hungry_list[i] - 1], NULL, philosopher, &ids[hungry_list[i] - 1]);
        sleep(3);
    }

    for (int i = 0; i < num_hungry; i++) {
        pthread_join(philosophers[hungry_list[i] - 1], NULL);
    }

    printf("\n1. One can eat at a time\n2. Two can eat at a time\n3. Exit\n");
    return 0;
}
