#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int main()
{
    int n, m;
    int allocation[MAX][MAX], request[MAX][MAX];
    int available[MAX], work[MAX];

    bool finish[MAX] = {false};

    printf("Enter number of processes and resources: ");
    scanf("%d%d", &n, &m);

    printf("Enter Allocation Matrix:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Request Matrix:\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources:\n");

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
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
                bool possible = true;

                for (int j = 0; j < m; j++)
                {
                    if (request[i][j] > work[j])
                    {
                        possible = false;
                        break;
                    }
                }

                if (possible)
                {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found)
            break;
    }

    bool deadlock = false;

    printf("\nProcesses in Deadlock: ");

    for (int i = 0; i < n; i++)
    {
        if (!finish[i])
        {
            printf("P%d ", i);
            deadlock = true;
        }
    }

    if (!deadlock)
        printf("None");

    printf("\n");

    return 0;
}