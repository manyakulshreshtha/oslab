#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main()
{
    int n, m;
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int safeSeq[MAX_PROCESSES];
    bool finish[MAX_PROCESSES];
    int work[MAX_RESOURCES];
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("Enter Maximum Demand Matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }
    printf("Enter Available Resources:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        finish[i] = false;
    }
    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }
    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canFinish = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish)
                {
                    for (int k = 0; k < m; k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    safeSeq[count] = i;
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found)
        {
            break;
        }
    }
    bool safe = true;
    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            safe = false;
            break;
        }
    }
    if (safe)
    {
        printf("\nSystem is in SAFE state.\n");
        printf("Safe Sequence: ");
        for (int i = 0; i < n; i++)
        {
            printf("P%d", safeSeq[i]);
            if (i != n - 1)
            {
                printf(" -> ");
            }
        }
        printf("\n");
    }
    else
    {
        printf("\nSystem is NOT in safe state.\n");
        return 0;
    }
    int process;
    int request[MAX_RESOURCES];
    printf("\nEnter process number making request: ");
    scanf("%d", &process);
    printf("Enter request vector:\n");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &request[i]);
    }
    for (int i = 0; i < m; i++)
    {
        if (request[i] > need[process][i])
        {
            printf("\nError: Request exceeds process need.\n");

            return 0;
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (request[i] > available[i])
        {
            printf("\nResources not available. Process must wait.\n");

            return 0;
        }
    }
    for (int i = 0; i < m; i++)
    {
        available[i] -= request[i];

        allocation[process][i] += request[i];

        need[process][i] -= request[i];
    }
    for (int i = 0; i < n; i++)
    {
        finish[i] = false;
    }
    for (int i = 0; i < m; i++)
    {
        work[i] = available[i];
    }
    count = 0;
    while (count < n)
    {
        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canFinish = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish)
                {
                    for (int k = 0; k < m; k++)
                    {
                        work[k] += allocation[i][k];
                    }
                    safeSeq[count] = i;
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found)
        {
            break;
        }
    }
    safe = true;
    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            safe = false;
            break;
        }
    }
    if (safe)
    {
        printf("\nRequest can be GRANTED.\n");
        printf("New Safe Sequence: ");
        for (int i = 0; i < n; i++)
        {
            printf("P%d", safeSeq[i]);

            if (i != n - 1)
            {
                printf(" -> ");
            }
        }
        printf("\n");
    }
    else
    {
        printf("\nRequest CANNOT be granted.\n");
        printf("System will enter unsafe state.\n");
    }
    return 0;
}