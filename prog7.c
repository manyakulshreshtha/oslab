#include <stdio.h>
#include <stdbool.h>

#define MAX 100

/* ---------------- FIFO Page Replacement ---------------- */
void fifo(int pages[], int n, int capacity)
{
    int frames[MAX];
    int front = 0, count = 0, faults = 0;

    printf("\n--- FIFO Page Replacement ---\n");

    for (int i = 0; i < n; i++)
    {
        bool found = false;

        /* Check if page already exists in frame */
        for (int j = 0; j < count; j++)
        {
            if (frames[j] == pages[i])
            {
                found = true;
                break;
            }
        }

        /* Page fault occurs */
        if (!found)
        {
            if (count < capacity)
            {
                frames[count++] = pages[i];
            }
            else
            {
                frames[front] = pages[i];
                front = (front + 1) % capacity;
            }
            faults++;
        }

        printf("Page %d -> [", pages[i]);
        for (int j = 0; j < count; j++)
        {
            printf("%d", frames[j]);
            if (j < count - 1)
                printf(" ");
        }
        printf("]\n");
    }

    printf("Total Page Faults (FIFO): %d\n", faults);
}

/* ---------------- LRU Page Replacement ---------------- */
void lru(int pages[], int n, int capacity)
{
    int frames[MAX];
    int count = 0, faults = 0;

    printf("\n--- LRU Page Replacement ---\n");

    for (int i = 0; i < n; i++)
    {
        bool found = false;

        /* Check if page is already present */
        for (int j = 0; j < count; j++)
        {
            if (frames[j] == pages[i])
            {
                found = true;

                /* Move recently used page to the end */
                int temp = frames[j];

                for (int k = j; k < count - 1; k++)
                    frames[k] = frames[k + 1];

                frames[count - 1] = temp;
                break;
            }
        }

        /* Page fault */
        if (!found)
        {
            if (count < capacity)
            {
                frames[count++] = pages[i];
            }
            else
            {
                /* Remove least recently used page */
                for (int k = 0; k < capacity - 1; k++)
                    frames[k] = frames[k + 1];

                frames[capacity - 1] = pages[i];
            }

            faults++;
        }

        printf("Page %d -> [", pages[i]);
        for (int j = 0; j < count; j++)
        {
            printf("%d", frames[j]);
            if (j < count - 1)
                printf(" ");
        }
        printf("]\n");
    }

    printf("Total Page Faults (LRU): %d\n", faults);
}

/* ---------------- Optimal Page Replacement ---------------- */
void optimal(int pages[], int n, int capacity)
{
    int frames[MAX];
    int count = 0, faults = 0;

    printf("\n--- Optimal Page Replacement ---\n");

    for (int i = 0; i < n; i++)
    {
        bool found = false;

        /* Check if page is already in frame */
        for (int j = 0; j < count; j++)
        {
            if (frames[j] == pages[i])
            {
                found = true;
                break;
            }
        }

        /* Page fault */
        if (!found)
        {
            if (count < capacity)
            {
                frames[count++] = pages[i];
            }
            else
            {
                int farthest = -1;
                int index = -1;

                /* Find page used farthest in future */
                for (int j = 0; j < capacity; j++)
                {
                    int k;

                    for (k = i + 1; k < n; k++)
                    {
                        if (frames[j] == pages[k])
                            break;
                    }

                    if (k > farthest)
                    {
                        farthest = k;
                        index = j;
                    }
                }

                frames[index] = pages[i];
            }

            faults++;
        }

        printf("Page %d -> [", pages[i]);
        for (int j = 0; j < count; j++)
        {
            printf("%d", frames[j]);
            if (j < count - 1)
                printf(" ");
        }
        printf("]\n");
    }

    printf("Total Page Faults (Optimal): %d\n", faults);
}

/* ---------------- Main Function ---------------- */
int main()
{
    int n, capacity;
    int pages[MAX];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &capacity);

    fifo(pages, n, capacity);
    lru(pages, n, capacity);
    optimal(pages, n, capacity);

    return 0;
}