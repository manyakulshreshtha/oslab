#define max 10
#include <stdio.h>

struct process {
    int at;   
    int bt;   
    int rt;   
    int wt;   
    int tat; 
    int ct;   
    int done; 
};
void SRTF(struct process p[], int n)
{
    int completed = 0;
    int t = 0; 
    float total_wt = 0, total_tat = 0;
    while (completed < n)
    {
        int idx = -1;
        int min_rt = 9999;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= t && p[i].done == 0)
            {
                if (p[i].rt < min_rt)
                {
                    min_rt = p[i].rt;
                    idx = i;
                }
                else if (p[i].rt == min_rt)
                {
                    if (p[i].at < p[idx].at)
                    {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1)
        {
            p[idx].rt--;
            t++;

            if (p[idx].rt == 0)
            {
                p[idx].ct = t;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                total_wt += p[idx].wt;
                total_tat += p[idx].tat;

                p[idx].done = 1;
                completed++;
            }
        }
        else
        {
            t++; 
        }
    }

    printf("\nID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i, p[i].at, p[i].bt, p[i].ct,
               p[i].wt, p[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main()
{
    int n;
    struct process p[max];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time for process %d: ", i);
        scanf("%d", &p[i].at);

        printf("Enter burst time for process %d: ", i);
        scanf("%d", &p[i].bt);

        p[i].rt = p[i].bt; 
        p[i].done = 0;
    }
    SRTF(p, n);
    return 0;
}