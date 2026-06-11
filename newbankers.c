#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

void calculateNeed(int n, int m,
                   int max[][MAX_R],
                   int allocation[][MAX_R],
                   int need[][MAX_R])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            need[i][j] =
            max[i][j] - allocation[i][j];
        }
    }
}

void printNeedMatrix(int n,int m,
                     int need[][MAX_R])
{
    printf("\nNEED MATRIX\n");

    for(int i=0;i<n;i++)
    {
        printf("P%d : ",i);

        for(int j=0;j<m;j++)
        {
            printf("%d ",need[i][j]);
        }

        printf("\n");
    }
}

bool isSafe(int n,
            int m,
            int allocation[][MAX_R],
            int need[][MAX_R],
            int available[],
            int safeSeq[])
{
    int work[MAX_R];
    bool finish[MAX_P];

    for(int i=0;i<m;i++)
    {
        work[i] = available[i];
    }

    for(int i=0;i<n;i++)
    {
        finish[i] = false;
    }

    int count = 0;

    while(count < n)
    {
        bool found = false;

        for(int i=0;i<n;i++)
        {
            if(finish[i])
                continue;

            bool canFinish = true;

            for(int j=0;j<m;j++)
            {
                if(need[i][j] > work[j])
                {
                    canFinish = false;
                    break;
                }
            }

            if(canFinish)
            {
                for(int j=0;j<m;j++)
                {
                    work[j] += allocation[i][j];
                }

                safeSeq[count] = i;

                finish[i] = true;

                count++;

                found = true;
            }
        }

        if(!found)
        {
            return false;
        }
    }

    return true;
}

bool requestResources(int process,
                      int request[],
                      int n,
                      int m,
                      int allocation[][MAX_R],
                      int need[][MAX_R],
                      int available[],
                      int safeSeq[])
{
    /* Check Request <= Need */

    for(int i=0;i<m;i++)
    {
        if(request[i] > need[process][i])
        {
            printf("\nERROR: Request exceeds Need.\n");
            return false;
        }
    }

    /* Check Request <= Available */

    for(int i=0;i<m;i++)
    {
        if(request[i] > available[i])
        {
            printf("\nResources not available.\n");
            return false;
        }
    }

    /* Pretend Allocation */

    for(int i=0;i<m;i++)
    {
        available[i] -= request[i];

        allocation[process][i] += request[i];

        need[process][i] -= request[i];
    }

    /* Check Safety */

    if(isSafe(n,m,
              allocation,
              need,
              available,
              safeSeq))
    {
        return true;
    }

    /* Rollback */

    for(int i=0;i<m;i++)
    {
        available[i] += request[i];

        allocation[process][i] -= request[i];

        need[process][i] += request[i];
    }

    return false;
}

int main()
{
    int n,m;

    int allocation[MAX_P][MAX_R];
    int max[MAX_P][MAX_R];
    int need[MAX_P][MAX_R];

    int available[MAX_R];

    int safeSeq[MAX_P];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("Enter number of resources: ");
    scanf("%d",&m);

    printf("\nEnter Allocation Matrix\n");

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&allocation[i][j]);
        }
    }

    printf("\nEnter Maximum Matrix\n");

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }

    printf("\nEnter Available Vector\n");

    for(int i=0;i<m;i++)
    {
        scanf("%d",&available[i]);
    }

    calculateNeed(n,m,max,
                  allocation,
                  need);

    printNeedMatrix(n,m,need);

    if(isSafe(n,m,
              allocation,
              need,
              available,
              safeSeq))
    {
        printf("\nSYSTEM IS SAFE\n");

        printf("Safe Sequence:\n");

        for(int i=0;i<n;i++)
        {
            printf("P%d",safeSeq[i]);

            if(i != n-1)
            {
                printf(" -> ");
            }
        }

        printf("\n");
    }
    else
    {
        printf("\nSYSTEM IS UNSAFE\n");
        return 0;
    }

    int process;
    int request[MAX_R];

    printf("\nEnter process making request: ");
    scanf("%d",&process);

    printf("Enter request vector:\n");

    for(int i=0;i<m;i++)
    {
        scanf("%d",&request[i]);
    }

    if(requestResources(process,
                        request,
                        n,
                        m,
                        allocation,
                        need,
                        available,
                        safeSeq))
    {
        printf("\nREQUEST GRANTED\n");

        printf("New Safe Sequence:\n");

        for(int i=0;i<n;i++)
        {
            printf("P%d",safeSeq[i]);

            if(i != n-1)
            {
                printf(" -> ");
            }
        }

        printf("\n");
    }
    else
    {
        printf("\nREQUEST DENIED\n");
        printf("System would become unsafe.\n");
    }

    return 0;
}
