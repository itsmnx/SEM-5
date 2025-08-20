//LAB-6
//20-08-2025

#include<stdio.h>
#define MAX 100
void sjf_non_preemptive(int n, int at[], int bt[]) {
    int ct[MAX], tat[MAX], wt[MAX], completed[MAX] = {0};
    int currentTime = 0, completedCount = 0;
    float totalWT = 0, totalTAT = 0;
    while (completedCount != n) {
        int idx = -1;
        int minBT = 1e9;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= currentTime && bt[i] < minBT) {
                minBT = bt[i];
                idx = i;
            }
        }
        if (idx != -1) {
            ct[idx] = currentTime + bt[idx];
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed[idx] = 1;
            completedCount++;
            currentTime = ct[idx];
        } else {
            currentTime++;
        }
    }
    printf("\nNon-Preemptive SJF:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
        totalWT += wt[i];
        totalTAT += tat[i];
    }
    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}

void sjf_preemptive(int n, int at[], int bt[]) {
    int rt[MAX], ct[MAX], tat[MAX], wt[MAX];
    int completed = 0, time = 0, minRT, shortest = -1;
    int done[MAX] = {0};
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++)
        rt[i] = bt[i];
    while (completed != n) {
        minRT = 1e9;
        shortest = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0 && rt[i] < minRT) {
                minRT = rt[i];
                shortest = i;
            }
        }
        if (shortest == -1) {
            time++;
            continue;
        }
        rt[shortest]--;
        time++;
        if (rt[shortest] == 0) {
            completed++;
            ct[shortest] = time;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
        }
    }
    printf("\nPreemptive SJF (SRTF):\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
        totalWT += wt[i];
        totalTAT += tat[i];
    }
    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}


int main() {
    int n, choice;
    int at[MAX], bt[MAX];
    do {
        printf("\n=== SJF Scheduling Menu ===\n");
        printf("1. Preemptive SJF (SRTF)\n");
        printf("2. Non-Preemptive SJF\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 0)
            break;
        printf("Enter number of processes: ");
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            printf("Enter Arrival Time for Process %d: ", i+1);
            scanf("%d", &at[i]);
            printf("Enter Burst Time for Process %d: ", i+1);
            scanf("%d", &bt[i]);
        }
        if (choice == 1)
            sjf_preemptive(n, at, bt);
        else if (choice == 2)
            sjf_non_preemptive(n, at, bt);
        else
            printf("Invalid choice!\n");
    } while (choice != 0);

    return 0;
}
