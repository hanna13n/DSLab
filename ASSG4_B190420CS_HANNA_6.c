#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef struct Node
{
    int key;
    char mark;
    int d;
    struct Node *right, *left, *parent, *child;
    struct Node *next;
} node;

typedef struct fibonacci_heap
{
    node *min;
    int n;
} fibheap;

typedef struct queue
{
    node *head;
    node *tail;
} queue;

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
        q->tail->next = x;
        q->tail = q->tail->next;
    }
}

node *dequeue(queue *q)
{
    if (queueempty(q) == -1)
        return NULL;

    node *p = q->head;
    if (q->head == q->tail)
        q->tail = NULL;

    q->head = q->head->next;

    return p;
}

node *create_node(int k)
{
    node *temp;
    temp = (node *)malloc(sizeof(node));
    temp->key = k;
    temp->d = 0;
    temp->mark = 'f';
    temp->right = NULL;
    temp->left = NULL;
    temp->child = NULL;
    temp->parent = NULL;
    temp->next = NULL;
    return temp;
}

void insert_list(node *start, node *x)
{
    if (!start)
    {
        start = x;
        start->right = x;
        start->left = x;
        return;
    }
    node *p = start->left;
    x->right = start;
    start->left = x;
    x->left = p;
    p->right = x;
}

node *delete_list(node *start, node *x)
{
    if (!start)
        return x;
    if (x == start && x->right == start)
        start = NULL;
    else if (x == start)
    {
        node *p = x->left;
        start = start->right;
        p->right = start;
        start->left = p;
    }
    else if (x->right == start)
    {
        x->left->right = start;
        start->left = x->left;
    }
    else
    {
        x->left->right = x->right;
        x->right->left = x->left;
    }
    return x;
}

fibheap *makeheap()
{
    fibheap *h = (fibheap *)malloc(sizeof(fibheap));
    h->min = NULL;
    h->n = 0;
    return h;
}

void insert(fibheap *h, node *x)
{
    insert_list(h->min, x);
    if (!h->min)
        h->min = x;
    else
    {
        if (x->key < h->min->key)
            h->min = x;
    }
    h->n = h->n + 1;
}

node *minimum(fibheap *h)
{
    return h->min;
}

void link(fibheap *h, node *y, node *x)
{
    y = delete_list(h->min, y);
    if (y == y->right)
        h->min = NULL;
    else if (h->min == y)
        h->min = y->right;
    y->left = NULL;
    y->right = NULL;
    insert_list(x->child, y);
    if (!x->child)
        x->child = y;
    else
    {
        if (y->key < x->child->key)
            x->child = y;
    }
    y->parent = x;
    x->d = x->d + 1;
    y->mark = 'f';
}
void consolidate(fibheap *h)
{
    int dn = ceil(log(h->n) / log(2));
    node **a = (node **)malloc(dn * sizeof(node *));
    int i, d;
    for (i = 0; i < dn; i++)
        a[i] = NULL;
    node *w = h->min, *x, *y, *temp;
    do
    {
        node *x = w;
        d = x->d;
        while (a[d])
        {
            y = a[d];
            if (x->key > y->key)
            {
                temp = y;
                y = x;
                x = temp;
            }
            link(h, y, x);
            a[d] = NULL;
            d++;
        }
        a[d] = x;
        w = x->right;
    } while (w != h->min);
    h->min = NULL;
    for (i = 0; i < dn; i++)
        if (a[i])
            if (!h->min)
                h->min = a[i];
            else
            {
                if (a[i]->key < h->min->key)
                    h->min = a[i];
            }
}
node *extractmin(fibheap *h)
{
    node *z = h->min;
    if (z)
    {
        node *x = z->child;
        node *y;
        while (x)
        {
            y = x->right;
            if (x->left)
                x->left->right = NULL;
            if (x->right)
                x->right->left = NULL;
            x->left = NULL;
            x->right = NULL;
            insert_list(h->min, x);
            x->parent = NULL;
            x = y;
            if (x == z->child)
                break;
        }
        z = delete_list(h->min, z);
        if (z == z->right)
            h->min = NULL;
        else
        {
            h->min = z->right;
            consolidate(h);
        }
        z->right = NULL;
        z->left = NULL;
        h->n = h->n - 1;
    }
    return z;
}

void cut(fibheap *h, node *x, node *y)
{
    x = delete_list(y->child, x);
    if (x == x->right)
        y->child = NULL;
    else if (y->child == x)
        y->child = x->right;
    x->parent = NULL;
    x->right = NULL;
    x->left = NULL;
    y->d -= 1;
    insert_list(h->min, x);
    if (!h->min)
        h->min = x;
    x->mark = 'f';
}
void cascading_cut(fibheap *h, node *y)
{
    node *z = y->parent;
    if (z)
        if (y->mark == 'f')
            y->mark = 't';
        else
        {
            cut(h, y, z);
            cascading_cut(h, z);
        }
}
node *decreasekey(fibheap *h, node *x, int k)
{
    if (!x)
        return NULL;
    x->key = k;
    node *y = x->parent;
    if (y && x->key < y->key)
    {
        cut(h, x, y);
        cascading_cut(h, y);
    }
    if (x->key < h->min->key)
        h->min = x;
    return x;
}

node *search(fibheap *h, int k)
{
    if (!h->min)
        return NULL;
    node *p = h->min, *r = NULL;
    queue q;
    q.head = NULL;
    q.tail = NULL;
    do
    {
        r = p;
        do
        {
            if (p)
            {
                if (p->key == k)
                    return p;
                else if (p->child && p->key < k)
                    enqueue(&q, p->child);
                p = p->right;
            }
        } while (p != r);
        p = dequeue(&q);
    } while (p && p != h->min);
    return NULL;
}

int Delete(fibheap *h, node *x)
{
    if (!x || !h->min)
        return -1;
    int k = x->key;
    decreasekey(h, x, -1000001);
    extractmin(h);
    return k;
}

void printheap(fibheap *h)
{
    node *p = h->min;
    if (h->min)
    {
        printf("%d ", p->key);
        p = p->right;
        while (p != h->min)
        {
            printf("%d ", p->key);
            p = p->right;
        }
    }
}

int main()
{
    fibheap h = *(makeheap());
    char ch;
    node *n = (node *)malloc(sizeof(node));
    int k, z;
menu:
    scanf("%c", &ch);

    switch (ch)
    {
    case 'i':
        scanf("%d", &k);
        insert(&h, create_node(k));
        break;
    case 'm':
        if (minimum(&h))
            printf("%d\n", minimum(&h)->key);
        else
            printf("%d\n", -1);
        break;
    case 'x':
        n = extractmin(&h);
        if (n)
            printf("%d\n", n->key);
        else
            printf("%d\n", -1);
        break;
    case 'r':
        scanf("%d %d", &k, &z);
        if (k >= z)
            n = decreasekey(&h, search(&h, k), z);
        else
            printf("%d\n", -1);
        if (n)
            printf("%d\n", n->key);
        else
            printf("%d\n", -1);
        break;
    case 'd':
        scanf("%d", &k);
        printf("%d\n", Delete(&h, search(&h, k)));
        break;
    case 'p':
        printheap(&h);
        printf("\n");
        break;
    case 'e':
        exit(0);
    }

    goto menu;
    return 0;
}