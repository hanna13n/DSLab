#include <stdio.h>
#include <stdlib.h>

int time;
typedef struct vertex_node
{
    int key;
    char color;
    int d, f;
    struct vertex_node **next, *qnext, *pi;
} node;
typedef struct adjacency_list
{
    node *head;
} adjlist;
typedef struct graph
{
    int v;
    adjlist *array;
} graph;

typedef struct queue
{
    node *head;
    node *tail;
} queue;

node *create_node(int k)
{
    node *temp;
    temp = (node *)malloc(sizeof(node));
    temp->key = k;
    temp->color = 'w';
    temp->d = 10001;
    temp->qnext = NULL;
    temp->pi = NULL;
    return temp;
}

void insert_adjlist(adjlist *l, node *x)
{
    if (l->head == NULL)
        l->head = x;
    else
    {
        node *p = l->head;
        while (p->next[l->head->key] != NULL)
            p = p->next[l->head->key];
        p->next[l->head->key] = x;
    }
}

int queueempty(queue *q)
{
    if (q->head == NULL)
        return -1;
    else
        return 1;
}

void enqueue(queue *q, node *x)
{
    if (queueempty(q) == -1)
    {
        q->head = x;
        q->tail = x;
    }
    else
    {
        q->tail->qnext = x;
        q->tail = q->tail->qnext;
    }
}

node *dequeue(queue *q)
{
    if (queueempty(q) == -1)
        return NULL;

    node *p = q->head;
    if (q->head == q->tail)
        q->tail = NULL;

    q->head = q->head->qnext;
    return p;
}

void bfs(graph *g, node *s)
{
    int i;
    for (i = 0; i < g->v; i++)
    {
        if (g->array[i].head != s)
        {
            g->array[i].head->color = 'w';
            g->array[i].head->d = 10001;
            g->array[i].head->pi = NULL;
        }
    }
    s->color = 'g';
    s->d = 0;
    s->pi = NULL;
    node *u, *v;
    queue q;
    q.head = NULL;
    q.tail = NULL;
    enqueue(&q, s);
    while (queueempty(&q) != -1)
    {
        u = dequeue(&q);
        printf("%d ", u->key);
        v = u->next[u->key];
        while (v != NULL && v != u)
        {
            if (v->color == 'w')
            {
                v->color = 'g';
                v->d = u->d + 1;
                v->pi = u;
                enqueue(&q, v);
            }
            v = v->next[u->key];
        }
        u->color = 'b';
    }
}

void dfs_visit(graph *g, node *u)
{
    time++;
    u->d = time;
    printf("%d ", u->key);
    u->color = 'g';
    node *v = u->next[u->key];
    while (v != NULL && v != u)
    {
        if (v->color == 'w')
        {
            v->pi = u;
            dfs_visit(g, v);
        }
        v = v->next[u->key];
    }
    u->color = 'b';
    time++;
    u->f = time;
}

void dfs(graph *g)
{
    int i;
    for (i = 0; i < g->v; i++)
    {
        g->array[i].head->color = 'w';
        g->array[i].head->pi = NULL;
    }
    time = 0;
    for (i = 0; i < g->v; i++)
        if (g->array[i].head->color == 'w')
            dfs_visit(g, g->array[i].head);
}

int main()
{
    graph g;
    int m, i, j, k;
    scanf("%d %d", &g.v, &m);
    g.array = (adjlist *)malloc(g.v * sizeof(adjlist));
    for (i = 0; i < g.v; i++)
    {
        g.array[i].head = create_node(i);
        g.array[i].head->next = (node **)malloc(g.v * sizeof(node *));
        for (j = 0; j < g.v; j++)
        {
            g.array[i].head->next[j] = (node *)malloc(sizeof(node));
            g.array[i].head->next[j] = NULL;
        }
    }
    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &j, &k);
        insert_adjlist(&g.array[j], g.array[k].head);
    }
    scanf("%d", &k);
    node *s = g.array[k].head;
    bfs(&g, s);
    printf("\n");
    dfs(&g);

    return 0;
}