//os lab:lab7-28/8/25

#include <stdio.h>
#define MAX 100
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void sortByArrival(int n, int at[], int bt[], int pr[], int pid[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                swap(&at[i], &at[j]);
                swap(&bt[i], &bt[j]);
                swap(&pr[i], &pr[j]);
                swap(&pid[i], &pid[j]);
            }
        }
    }
}
void printGanttChartNonPreemptive(int n, int at[], int bt[], int ct[], int pid[]) {
    printf("\nGantt Chart (Non-Preemptive Priority):\n ");
    for (int i = 0; i < n; i++) {
        printf("|  P%d  ", pid[i]);
    }
    printf("|\n0");
    for (int i = 0; i < n; i++) {
        printf("     %d", ct[i]);
    }
    printf("\n");
}
void priority_non_preemptive(int n, int at[], int bt[], int pr[], int pid[]) {
    int ct[MAX], tat[MAX], wt[MAX], completed[MAX] = {0};
    int currentTime = 0, completedCount = 0;
    float totalWT = 0, totalTAT = 0;
    while (completedCount != n) {
        int idx = -1;
        int highestPr = 1e9;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= currentTime) {
                if (pr[i] < highestPr) {
                    highestPr = pr[i];
                    idx = i;
                } else if (pr[i] == highestPr) {
                    if (at[i] < at[idx]) {
                        idx = i;
                    }
                }
            }
        }
        if (idx != -1) {
            if(currentTime < at[idx]) currentTime = at[idx];
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
    printf("\nNon-Preemptive Priority Scheduling:\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
        totalWT += wt[i];
        totalTAT += tat[i];
    }
    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    printGanttChartNonPreemptive(n, at, bt, ct, pid);
}

void printGanttChartPreemptive(int n, int timeline[], int pidx[], int length, int pid[]) {
    printf("\nGantt Chart (Preemptive Priority):\n ");
    for (int i = 0; i < length; i++) {
        printf("| P%d ", pid[pidx[i]]);
    }
    printf("|\n%d", timeline[0]);
    for (int i = 1; i <= length; i++) {
        printf("    %d", timeline[i]);
    }
    printf("\n");
}

void priority_preemptive(int n, int at[], int bt[], int pr[], int pid[]) {
    int rt[MAX], ct[MAX], tat[MAX], wt[MAX];
    int completed = 0, time = 0, highestPr;
    int shortest = -1;
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++)
        rt[i] = bt[i];
    int timeline[1000];
    int pidx[1000];
    int length = 0;
    int prev = -1;
    while (completed != n) {
        highestPr = 1e9;
        shortest = -1;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                if (pr[i] < highestPr) {
                    highestPr = pr[i];
                    shortest = i;
                } else if (pr[i] == highestPr) {
                    if (at[i] < at[shortest]) shortest = i;
                }
            }
        }
        if (shortest == -1) {
            time++;
            continue;
        }
        if (prev != shortest) {
            timeline[length] = time;
            pidx[length] = shortest;
            length++;
            prev = shortest;
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
    timeline[length] = time;
    printf("\nPreemptive Priority Scheduling:\n");
    printf("PID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
        totalWT += wt[i];
        totalTAT += tat[i];
    }
    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
    printGanttChartPreemptive(n, timeline, pidx, length, pid);
}

int main() {
    int n, choice;
    int at[MAX], bt[MAX], pr[MAX], pid[MAX];

    do {
        printf("\n=== Priority Scheduling Menu ===\n");
        printf("1. Preemptive Priority Scheduling\n");
        printf("2. Non-Preemptive Priority Scheduling\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 0)
            break;

        if (choice != 1 && choice != 2) {
            printf("Invalid choice!\n");
            continue;
        }

        printf("Enter number of processes: ");
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            pid[i] = i + 1;
            printf("Enter Arrival Time for Process %d: ", pid[i]);
            scanf("%d", &at[i]);
            printf("Enter Burst Time for Process %d: ", pid[i]);
            scanf("%d", &bt[i]);
            printf("Enter Priority for Process %d (lower number = higher priority): ", pid[i]);
            scanf("%d", &pr[i]);
        }

        sortByArrival(n, at, bt, pr, pid);

        if (choice == 1)
            priority_preemptive(n, at, bt, pr, pid);
        else
            priority_non_preemptive(n, at, bt, pr, pid);

    } while (choice != 0);

    return 0;
}

