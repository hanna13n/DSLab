#include <stdio.h>
#include <stdlib.h>

typedef struct graph
{
    int v;
    int *key;
    int *pi;
    int **adj;
} graph;

int extract_min(graph *g, int a[])
{
    int min = 10002, i, p;
    for (i = 0; i < g->v; i++)
    {
        if (!a[i] && g->key[i] < min)
        {
            min = g->key[i];
            p = i;
        }
    }
    return p;
}

int isempty(int a[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!a[i])
            return 0;
    }
    return 1;
}
int sumprims(graph *g)
{
    int i, s = 0;
    for (i = 1; i < g->v; i++)
        s = s + g->key[i];
    return s;
}

void primsmst(graph *g)
{
    int i, u;
    int *q = (int *)malloc(g->v * sizeof(int)), *p = (int *)malloc(g->v * sizeof(int));
    g->pi = (int *)malloc(g->v * sizeof(int));
    g->key = (int *)malloc(g->v * sizeof(int));

    for (i = 0; i < g->v; i++)
    {
        g->key[i] = 10001;
        g->pi[i] = -1;
        q[i] = 0;
    }
    g->key[0] = 0;
    while (!isempty(q, g->v))
    {
        u = extract_min(g, q);
        q[u] = 1;
        for (i = 0; i < g->v; i++)
        {
            if (g->adj[u][i] != -10001)
            {
                if (q[i] == 0 && g->adj[u][i] < g->key[i])
                {
                    g->pi[i] = u;
                    g->key[i] = g->adj[u][i];
                }
            }
        }
    }
    printf("%d\n", sumprims(g));
}

int find(int i, graph *g)
{
    while (g->pi[i] != i)
        i = g->pi[i];
    return i;
}

void Union(int i, int j, graph *g)
{
    int a = find(i, g);
    int b = find(j, g);
    g->pi[a] = b;
}

void kruskalsmst(graph *g)
{
    int mc = 0, i, j, a, b, min;
    for (i = 0; i < g->v; i++)
        g->pi[i] = i;
    int ec = 0;
    while (ec < g->v - 1)
    {
        min = 10001;
        a = -1;
        b = -1;
        for (i = 0; i < g->v; i++)
            for (j = 0; j < g->v; j++)
            {
                if (find(i, g) != find(j, g) && g->adj[i][j] != -10001 && g->adj[i][j] < min)
                {
                    min = g->adj[i][j];
                    a = i;
                    b = j;
                }
            }
        ec++;
        Union(a, b, g);
        mc += min;
    }
    printf("%d\n", mc);
}

int main()
{
    char ch, c;
    int i, j, k;
    scanf("%c", &ch);
    graph g;
    scanf("%d", &g.v);
    g.adj = (int **)malloc(g.v * sizeof(int *));
    for (i = 0; i < g.v; i++)
    {
        g.adj[i] = (int *)malloc(g.v * sizeof(int));
        for (j = 0; j < g.v; j++)
            g.adj[i][j] = -10001;
    }
    for (i = 0; i < g.v; i++)
    {
        scanf("%d%c", &j, &c);
        while (c != '\n')
        {
            scanf("%d%c", &j, &c);
            g.adj[i][j] = 1;
        }
    }
    for (i = 0; i < g.v; i++)
    {
        scanf("%d%c", &j, &c);
        k = 0;
        while (c != '\n')
        {
            scanf("%d%c", &j, &c);
            while (k < g.v && g.adj[i][k] == -10001)
            {
                k++;
            }
            g.adj[i][k] = j;
            k++;
        }
    }
    switch (ch)
    {
    case 'a':
        kruskalsmst(&g);
        break;
    case 'b':
        primsmst(&g);
        break;
    }
    return 0;
}