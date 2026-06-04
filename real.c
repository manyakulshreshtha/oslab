#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct Process {
    int id;
    int bt;
    int deadline;
    int period;
    int share;
    int ct, wt, tat;
};

void resetProcesses(struct Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].ct = p[i].wt = p[i].tat = 0;
    }
}

void EDF(struct Process p[], int n) {
    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1-i; j++)
            if (p[j].deadline > p[j+1].deadline) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
    int time = 0;
    for (int i = 0; i < n; i++) {
        p[i].wt = time;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
    }
    printf("ID\tBT\tDeadline\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].id, p[i].bt,
               p[i].deadline, p[i].ct, p[i].wt, p[i].tat);
}

void RMS(struct Process p[], int n) {
    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-1-i; j++)
            if (p[j].period > p[j+1].period) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
    int time = 0;
    for (int i = 0; i < n; i++) {
        p[i].wt = time;
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
    }
    printf("ID\tBT\tPeriod\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].bt, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
}

void ProportionalShare(struct Process p[], int n) {
    printf("\n===== Proportional Share Scheduling =====\n");
    int remaining[MAX], time = 0, done = 0;
    for (int i = 0; i < n; i++)
        remaining[i] = p[i].bt;
    while (done < n) {
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                int timeSlice = (p[i].share > 0) ? 1 : 0;
                if (remaining[i] < timeSlice) timeSlice = remaining[i];
                time += timeSlice;
                remaining[i] -= timeSlice;
                if (remaining[i] == 0) {
                    p[i].ct = time;
                    p[i].tat = p[i].ct;
                    p[i].wt = p[i].tat - p[i].bt;
                    done++;
                }
            }
        }
    }
    printf("ID\tBT\tShare\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].bt, p[i].share,
               p[i].ct, p[i].wt, p[i].tat);
}

int main() {
    int n;
    struct Process p[MAX];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("\nEnter process details:\n");
    for (int i = 0; i < n; i++) {
        p[i].id = i;
        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);
        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);
        printf("Share (for Proportional): ");
        scanf("%d", &p[i].share);
    }
    resetProcesses(p, n);
    EDF(p, n);
    resetProcesses(p, n);
    RMS(p, n);
    resetProcesses(p, n);
    ProportionalShare(p, n);
    return 0;
}
