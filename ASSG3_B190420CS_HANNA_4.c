#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int k;
    int d;
    struct node *p, *child, *sibling;
    struct node *next; /*for queue nodes to print in level order.*/
} node;
typedef struct binomialheap
{
    node *head;
} heap;

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

heap *makeheap()
{
    heap *temp = (heap *)malloc(sizeof(heap));
    temp->head = NULL;
    return temp;
}

heap *mergeheap(heap *h1, heap *h2)
{
    node *p1 = h1->head;
    node *prev = NULL;
    node *p2 = h2->head;
    node *next = NULL;
    if (p2)
        next = p2->sibling;
    while (p1 != NULL && p2 != NULL)
    {
        if (p2->d < p1->d)
        {
            if (prev != NULL)
                prev->sibling = p2;
            else
                h1->head = p2;
            p2->sibling = p1;
            p2 = next;
            if (next != NULL)
                next = next->sibling;
        }
        prev = p1;
        p1 = p1->sibling;
    }
    if (p1 == NULL && p2 != NULL)
    {
        if (prev != NULL)
            prev->sibling = p2;
        else
            return h2;
    }
    return h1;
}
void binomial_link(node *y, node *z)
{
    y->p = z;
    y->sibling = z->child;
    z->child = y;
    z->d++;
}

heap *Union(heap *h1, heap *h2)
{
    heap *h = makeheap();
    h = mergeheap(h1, h2);
    h1 = NULL;
    h2 = NULL;

    node *prev = NULL, *x = h->head, *next = NULL;
    if (h->head)
        next = h->head->sibling;
    while (next != NULL)
    {
        if (x->d != next->d || (next->sibling != NULL && next->sibling->d == x->d))
        {
            prev = x;
            x = next;
        }
        else if (x->k <= next->k)
        {
            x->sibling = next->sibling;
            binomial_link(next, x);
        }
        else
        {
            if (prev == NULL)
                h->head = next;
            else
                prev->sibling = next;
            binomial_link(x, next);
            x = next;
        }
        next = x->sibling;
    }
    return h;
}

heap *insert(heap *h, int x)
{
    heap *h1 = makeheap();
    h1->head = (node *)malloc(sizeof(node));
    h1->head->k = x;
    h1->head->d = 0;
    h1->head->p = NULL;
    h1->head->child = NULL;
    h1->head->sibling = NULL;
    h1->head->next = NULL;
    h = Union(h, h1);
    return h;
}

node *minimum(heap *h)
{
    node *x = h->head, *y = h->head;
    int min;
    if (x)
        min = x->k;
    else
        return NULL;
    x = x->sibling;
    while (x != NULL)
    {
        if (x->k < min)
        {
            min = x->k;
            y = x;
        }
        x = x->sibling;
    }
    return y;
}

node *reverse(node *h)
{
    node *cursor, *pre;
    cursor = h;
    pre = NULL;

    while (cursor != NULL)
    {
        h = cursor;
        cursor = cursor->sibling;
        h->sibling = pre;
        pre = h;
    }
    return h;
}

int extractmin(heap *h)
{
    node *x = h->head, *y = h->head, *prev = NULL, *p = NULL;

    int min = -1;

    if (x)
        min = x->k;
    else
        return min;

    prev = x;
    x = x->sibling;

    while (x != NULL)
    {
        if (x->k < min)
        {
            min = x->k;
            y = x;
            p = prev;
        }
        prev = x;
        x = x->sibling;
    }

    if (h->head == y)
        h->head = y->sibling;
    else if (p)
        p->sibling = y->sibling;
    y->sibling = NULL;

    heap *h1 = makeheap();
    h1->head = reverse(y->child);

    y->child = h1->head;
    while (y->child)
    {
        y->child->p = NULL;
        y->child = y->child->sibling;
    }
    y->child = NULL;

    y = NULL;

    h->head = Union(h, h1)->head;
    return min;
}

node *searchheap(node *h, int k)
{
    if (h == NULL)
        return NULL;
    else if (k == h->k)
        return h;
    else
    {
        node *f = searchheap(h->child, k);
        if (f != NULL)
            return f;
    }
    return searchheap(h->sibling, k);
}
int decreasekey(heap *h, node *x, int k)
{
    if (x == NULL)
        return -1;
    x->k -= k;
    node *y = x, *z = x->p;
    int temp;
    while (z != NULL && y->k < z->k)
    {
        temp = y->k;
        y->k = z->k;
        z->k = temp;
        y = z;
        z = y->p;
    }
    return y->k;
}

void Delete(heap *h, int x)
{
    node *n = searchheap(h->head, x);
    if (n == NULL)
    {
        printf("%d\n", -1);
        return;
    }
    int d = n->k;
    if (d > 0)
        decreasekey(h, n, 1000001);
    else
        decreasekey(h, n, -1000001);
    extractmin(h);
    n = NULL;
    printf("%d\n", d);
}

void levelorder(node *r, queue *q)
{
    if (r == NULL)
        return;

    node *temp = r;
    while (temp)
    {
        if (temp->child)
            enqueue(q, temp->child);
        printf("%d ", temp->k);
        temp = temp->sibling;
    }
    levelorder(dequeue(q), q);
}

void printheap(heap *h)
{
    node *p = h->head;
    queue q;
    q.head = NULL;
    q.tail = NULL;
    while (p != NULL)
    {
        printf("%d ", p->k);
        if (p->child)
        {
            levelorder(p->child, &q);
        }
        p = p->sibling;
    }
}

int main()
{
    heap h = *(makeheap());
    char ch;
    node *n = (node *)malloc(sizeof(node));
    int k, z;
menu:
    scanf("%c", &ch);

    switch (ch)
    {
    case 'i':
        scanf("%d", &k);
        h = *(insert(&h, k));
        break;
    case 'm':
        n = minimum(&h);
        if (n)
            printf("%d\n", n->k);
        else
            printf("%d\n", -1);
        break;
    case 'x':
        k = extractmin(&h);
        printf("%d\n", k);
        break;
    case 'r':
        scanf("%d %d", &k, &z);
        if (k < z)
        {
            printf("%d\n", -1);
            break;
        }
        k = decreasekey(&h, searchheap(h.head, k), z);
        printf("%d\n", k);
        break;
    case 'd':
        scanf("%d", &k);
        Delete(&h, k);
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
