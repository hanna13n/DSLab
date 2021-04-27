#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int label;
    int key;
    int *w;
    struct node **next, *pi;
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

node *create_node(int k)
{
    node *temp;
    temp = (node *)malloc(sizeof(node));
    temp->key = 0;
    temp->label = k;
    temp->pi = NULL;
    return temp;
}

node *extract_min(graph *g, int a[])
{
    int min = 10002, i;
    node *p = NULL;
    for (i = 0; i < g->v; i++)
    {
        if (!a[i] && g->array[i].head->key < min)
        {
            min = g->array[i].head->key;
            p = g->array[i].head;
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

int sumprims(int p[], graph *g)
{
    int i, s = 0;
    for (i = 0; i < g->v; i++)
        s = s + g->array[i].head->key;
    return s;
}

void primsmst(graph *g)
{
    int i;
    int *q = (int *)malloc(g->v * sizeof(int)), *p = (int *)malloc(g->v * sizeof(int));
    node *u, *v;
    for (i = 0; i < g->v; i++)
    {
        g->array[i].head->key = 10001;
        g->array[i].head->pi = NULL;
        q[i] = 0;
    }
    g->array[0].head->key = 0;
    while (!isempty(q, g->v))
    {
        u = extract_min(g, q);

        q[u->label] = 1;
        v = g->array[u->label].head->next[u->label];
        while (v != NULL)
        {
            if (q[v->label] == 0 && v->w[u->label] < v->key)
            {
                v->pi = u;
                p[v->label] = u->label;
                v->key = v->w[u->label];
            }
            v = v->next[u->label];
        }
    }
    printf("%d\n", sumprims(p, g));
}

int find(int i, graph *g)
{
    while (g->array[i].head->pi->label != i)
        i = g->array[i].head->pi->label;
    return i;
}

void Union(int i, int j, graph *g)
{
    int a = find(i, g);
    int b = find(j, g);
    g->array[a].head->pi = g->array[b].head;
}

void kruskalsmst(graph *g)
{
    int mc = 0, i, j, a, b, min;
    for (i = 0; i < g->v; i++)
        g->array[i].head->pi = g->array[i].head;
    int ec = 0;
    node *u;
    while (ec < g->v - 1)
    {
        min = 10001;
        a = -1;
        b = -1;
        for (i = 0; i < g->v; i++)
        {
            u = g->array[i].head->next[i];
            while (u)
            {
                if (find(i, g) != find(u->label, g) && u->w[i] < min)
                {
                    a = i;
                    b = u->label;
                    min = u->w[i];
                }
                u = u->next[i];
            }
        }
        ec++;
        Union(a, b, g);
        mc += min;
    }
    printf("%d\n", mc);
}

void insert_adjlist(adjlist *l, node *x)
{
    if (l->head == NULL)
        l->head = x;
    else
    {
        node *p = l->head;
        while (p->next[l->head->label] != NULL)
            p = p->next[l->head->label];
        p->next[l->head->label] = x;
    }
}

int main()
{
    char ch, c;
    int i, j, k;
    scanf("%c", &ch);
    graph g;
    scanf("%d", &g.v);
    g.array = (adjlist *)malloc(g.v * sizeof(adjlist));
    for (i = 0; i < g.v; i++)
    {
        g.array[i].head = create_node(i);
        g.array[i].head->next = (node **)malloc(g.v * sizeof(node *));
        g.array[i].head->w = (int *)malloc(g.v * sizeof(int));
        for (j = 0; j < g.v; j++)
        {
            g.array[i].head->next[j] = (node *)malloc(sizeof(node));
            g.array[i].head->next[j] = NULL;
        }
    }
    for (i = 0; i < g.v; i++)
    {
        scanf("%d%c", &j, &c);
        while (c != '\n')
        {
            scanf("%d%c", &j, &c);
            insert_adjlist(&g.array[i], g.array[j].head);
        }
    }
    for (i = 0; i < g.v; i++)
    {
        node *p = g.array[i].head->next[i];
        scanf("%d%c", &k, &c);
        while (p != NULL)
        {
            scanf("%d%c", &k, &c);
            g.array[i].head->w[p->label] = k;
            p = p->next[i];
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