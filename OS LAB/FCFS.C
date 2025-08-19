//Practical-06
#include <stdio.h>
int main() {
    int n, i;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int arrival[n], burst[n], completion[n], waiting[n], turnaround[n];
    int current_time = 0;
    printf("Enter arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &arrival[i]);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &burst[i]);
    }
    for (i = 0; i < n; i++) {
        if (arrival[i] > current_time) {
            current_time = arrival[i];
        }
        completion[i] = current_time + burst[i];
        turnaround[i] = completion[i] - arrival[i];
        waiting[i] = turnaround[i] - burst[i];
        current_time = completion[i];
    }

    printf("\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", i + 1, arrival[i], burst[i], completion[i], waiting[i], turnaround[i]);
    }
 float avg_waiting = 0, avg_turnaround = 0;
    for (i = 0; i < n; i++) {
        avg_waiting += waiting[i];
        avg_turnaround += turnaround[i];
    }
    avg_waiting /= n;
    avg_turnaround /= n;
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround);
    return 0;
}
//MANAS JOSHI
//C-37
