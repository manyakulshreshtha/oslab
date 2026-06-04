#include <stdio.h>
#include <string.h>

#define MAX 100

void resetBlocks(int original[], int copy[], int size)
{
    for (int i = 0; i < size; i++)
        copy[i] = original[i];
}

void firstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[MAX];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }

    printf("\nFirst Fit\n");
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%s%d\n", i + 1, processSize[i],
               allocation[i] == -1 ? "" : "",
               allocation[i] == -1 ? 0 : allocation[i] + 1);
}

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[MAX];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n; i++)
    {
        int best = -1;

        for (int j = 0; j < m; j++)
            if (blockSize[j] >= processSize[i] &&
                (best == -1 || blockSize[j] < blockSize[best]))
                best = j;

        if (best != -1)
        {
            allocation[i] = best;
            blockSize[best] -= processSize[i];
        }
    }

    printf("\nBest Fit\n");
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++)
        if (allocation[i] != -1)
            printf("%d\t%d\t%d\n", i + 1, processSize[i], allocation[i] + 1);
        else
            printf("%d\t%d\tNot Allocated\n", i + 1, processSize[i]);
}

void worstFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[MAX];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n; i++)
    {
        int worst = -1;

        for (int j = 0; j < m; j++)
            if (blockSize[j] >= processSize[i] &&
                (worst == -1 || blockSize[j] > blockSize[worst]))
                worst = j;

        if (worst != -1)
        {
            allocation[i] = worst;
            blockSize[worst] -= processSize[i];
        }
    }

    printf("\nWorst Fit\n");
    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++)
        if (allocation[i] != -1)
            printf("%d\t%d\t%d\n", i + 1, processSize[i], allocation[i] + 1);
        else
            printf("%d\t%d\tNot Allocated\n", i + 1, processSize[i]);
}

int main()
{
    int m, n;
    int original[MAX], blockSize[MAX], processSize[MAX];

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter block sizes:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &original[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter process sizes:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    resetBlocks(original, blockSize, m);
    firstFit(blockSize, m, processSize, n);

    resetBlocks(original, blockSize, m);
    bestFit(blockSize, m, processSize, n);

    resetBlocks(original, blockSize, m);
    worstFit(blockSize, m, processSize, n);

    return 0;
}