#include <stdio.h>
#include <stdlib.h>

int main()
{
    int v, i, j;
    scanf("%d", &v);
    int **adj = (int **)malloc(v * sizeof(int *));
    for (i = 0; i < v; i++)
        adj[i] = (int *)malloc(v * sizeof(int));

    for (i = 0; i < v; i++)
        for (j = 0; j < v; j++)
            scanf("%d", &adj[i][j]);

    for (i = 0; i < v; i++)
    {
        printf("%d ", i);
        for (j = 0; j < v; j++)
            if (adj[i][j] == 1)
                printf("%d ", j);
        printf("\n");
    }
    return 0;
}