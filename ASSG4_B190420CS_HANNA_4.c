#include <stdio.h>
#include <stdlib.h>

int time;

typedef struct graph
{
    int v;
    int e;
    int *d, *f, *pi; /* d is used as distance and discovering time in bfs and dfs respectively */
    char *color;
    int **adj;
} graph;

typedef struct Queue
{
    int head;
    int tail;
    int n;
    int *a;
} queue;

int queuefull(queue *q)
{
    if (q->tail == q->head - 1 || (q->tail == q->n && q->head == 0))
        return -1;
    else
        return 1;
}

int queueempty(queue *q)
{
    if (q->head == -1 || q->head == q->tail)
        return -1;
    else
        return 1;
}

void enqueue(queue *q, int k)
{
    if (queuefull(q) == 1)
    {
        if (q->head == -1)
            q->head++;

        q->a[q->tail] = k;

        if (q->tail == q->n)
            q->tail = 0;
        else
            q->tail++;
    }
    else
        printf("\n%d", -1);
}

int dequeue(queue *q)
{
    if (queueempty(q) == -1)
        return -1;

    int x = q->a[q->head];

    if (q->head == q->n)
        q->head = 0;
    else
        q->head++;

    return x;
}

void bfs(graph *g, int s)
{
    int i;
    for (i = 0; i < g->v; i++)
    {
        if (i != s)
        {
            g->color[i] = 'w';
            g->d[i] = 10001;
            g->pi[i] = 0;
        }
    }
    g->color[s] = 'g';
    g->d[s] = 0;
    g->pi[s] = 0;

    int u, v;
    queue q;
    q.head = -1;
    q.tail = 0;
    q.n = 2 * g->v;
    q.a = (int *)malloc(q.n * sizeof(int));

    enqueue(&q, s);
    while (queueempty(&q) != -1)
    {
        u = dequeue(&q);
        printf("%d ", u);
        for (i = 0; i < g->v; i++)
        {
            if (g->adj[u][i] == 1)
            {
                if (g->color[i] == 'w')
                {
                    g->color[i] = 'g';
                    g->d[i] = g->d[u] + 1;
                    g->pi[i] = u;
                    enqueue(&q, i);
                }
            }
        }
        g->color[u] = 'b';
    }
}

void dfs_visit(graph *g, int u)
{
    time++;
    g->d[u] = time;
    printf("%d ", u);
    g->color[u] = 'g';

    int i;
    for (i = 0; i < g->v; i++)
    {
        if (g->adj[u][i] == 1)
        {
            if (g->color[i] == 'w')
            {
                g->pi[i] = u;
                dfs_visit(g, i);
            }
        }
    }

    g->color[u] = 'b';
    time++;
    g->f[u] = time;
}

void dfs(graph *g)
{
    int i;
    for (i = 0; i < g->v; i++)
    {
        g->color[i] = 'w';
        g->pi[i] = 0;
    }

    time = 0;
    for (i = 0; i < g->v; i++)
        if (g->color[i] == 'w')
            dfs_visit(g, i);
}

int main()
{
    graph g;
    scanf("%d %d", &g.v, &g.e);
    g.adj = (int **)malloc(g.v * sizeof(int *));
    g.color = (char *)malloc(g.v * sizeof(char));
    g.d = (int *)malloc(g.v * sizeof(int));
    g.f = (int *)malloc(g.v * sizeof(int));
    g.pi = (int *)malloc(g.v * sizeof(int));

    int i, j, k;
    for (i = 0; i < g.v; i++)
    {
        g.adj[i] = (int *)malloc(g.v * sizeof(int));
        for (j = 0; j < g.v; j++)
            g.adj[i][j] = 0;
    }

    for (i = 0; i < g.e; i++)
    {
        scanf("%d %d", &j, &k);
        g.adj[j][k] = 1;
    }

    scanf("%d", &k);
    bfs(&g, k);
    printf("\n");
    dfs(&g);

    return 0;
}