#include<stdio.h>

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void swap(struct process *a, struct process *b) {
    struct process temp = *a;
    *a = *b;
    *b = temp;
}

void sjf(struct process proc[], int n) {
    for(int i=0; i < n-1; i++) {
        for(int j=0; j < n-i-1; j++) {
            if(proc[j].burst_time > proc[j+1].burst_time) {
                swap(&proc[j],&proc[j+1]);
            }
        }
    }
    int completion_time = 0;
    float total_wt = 0;
    float total_tat = 0;

    for(int i=0; i < n; i++) {
        if(completion_time < proc[i].arrival_time) {
            completion_time = proc[i].arrival_time;
        }
        proc[i].waiting_time = completion_time - proc[i].arrival_time;
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
        completion_time += proc[i].burst_time;

        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
    }

    printf("SJF Scheduling\n");
    printf("PID\tAT\tBT\tWT\tTAT\n");
    for(int i=0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n",proc[i].pid,proc[i].arrival_time,proc[i].burst_time,
                proc[i].waiting_time,proc[i].turnaround_time);

    }

    printf("Average Waiting Time : %.2f\n",total_wt/n);
    printf("Average Turn Around Time : %.2f\n",total_tat/n);
}

int main() {
    int n;
    printf("Enter the number of process : ");
    scanf("%d",&n);

    struct process proc[n];

    for(int i=0; i < n; i++) {
        printf("Enter the details of process %d (AT BT) :",i+1);
        proc[i].pid = i+1;
        scanf("%d %d",&proc[i].arrival_time,&proc[i].burst_time);
    }

    sjf(proc,n);

    return 0;
}
