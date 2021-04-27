#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int key;
    int rank;
    struct node *parent;
} node;
node *a[10001] = {NULL}, *b[10001] = {NULL}, *c[10001] = {NULL}, *d[10001] = {NULL};
int sa = 0, sb = 0, sc = 0, sd = 0;

node *create_node(int k)
{
    node *temp;
    temp = (node *)malloc(sizeof(node));
    temp->key = k;
    temp->parent = NULL;
    return temp;
}

int makeset(int x)
{
    if (!a[x])
    {
        a[x] = create_node(x);
        b[x] = create_node(x);
        c[x] = create_node(x);
        d[x] = create_node(x);
        a[x]->parent = a[x];
        b[x]->parent = b[x];
        c[x]->parent = c[x];
        d[x]->parent = d[x];
        a[x]->rank = 0;
        b[x]->rank = 0;
        c[x]->rank = 0;
        d[x]->rank = 9;
        return x;
    }
    return -1;
}
node *find(node *x)
{
    if (!x)
        return NULL;
    else if (x == a[x->key] || x == b[x->key])
    {
        node *p = x;
        while (p->parent != p)
        {
            p = p->parent;
            if (p == a[p->key])
                sa++;
            else
                sb++;
        }
        if (p == a[p->key])
            sa++;
        else
            sb++;
        return p;
    }
    else
    {
        if (x->parent == x)
        {
            if (x == c[x->key])
                sc++;
            else
                sd++;
            return x;
        }
        else
            x->parent = find(x->parent);
        if (x == c[x->key])
            sc++;
        else
            sd++;
        return x->parent;
    }
}

node *link(node *x, node *y)
{
    if (x == a[x->key] || x == c[x->key])
    {
        if (x != y)
            y->parent = x;
        return x;
    }
    else
    {
        if (x->rank >= y->rank)
        {
            y->parent = x;
            if (x->rank == y->rank)
                x->rank++;
            return x;
        }
        else
        {
            x->parent = y;
            return y;
        }
    }
}

node *Union(node *x, node *y)
{
    if (!x || !y)
        return NULL;
    return link(find(x), find(y));
}

int main()
{

    int j, k;
    char ch;
    node *n = (node *)malloc(sizeof(node));

menu:
    scanf("%c", &ch);
    switch (ch)
    {
    case 'm':
        scanf("%d", &k);
        printf("%d\n", makeset(k));
        break;
    case 'f':
        scanf("%d", &k);
        n = find(a[k]);
        if (n)
            printf("%d ", n->key);
        else
            printf("%d ", -1);
        n = find(b[k]);
        if (n)
            printf("%d ", n->key);
        else
            printf("%d ", -1);
        n = find(c[k]);
        if (n)
            printf("%d ", n->key);
        else
            printf("%d ", -1);
        n = find(d[k]);
        if (n)
            printf("%d\n", n->key);
        else
            printf("%d\n", -1);
        break;
    case 'u':
        scanf("%d %d", &j, &k);
        n = Union(a[j], a[k]);
        if (n)
            printf("%d ", n->key);
        else
            printf("%d ", -1);
        n = Union(b[j], b[k]);
        if (n)
            printf("%d ", n->key);
        else
            printf("%d ", -1);
        n = Union(c[j], c[k]);
        if (n)
            printf("%d ", n->key);
        else
            printf("%d ", -1);
        n = Union(d[j], d[k]);
        if (n)
            printf("%d\n", n->key);
        else
            printf("%d\n", -1);
        break;
    case 's':
        printf("%d %d %d %d\n", sa, sb, sc, sd);
        exit(0);
    }
    goto menu;
    return 0;
}