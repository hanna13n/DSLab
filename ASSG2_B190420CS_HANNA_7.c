#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node
{
    int key;
    struct node *left, *right, *p, *next;

} node;

typedef struct tree
{
    node *root;

} tree;

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
    temp->left = NULL;
    temp->right = NULL;
    temp->next = NULL;
    temp->p = NULL;

    return temp;
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

void insert(tree *t, node *x)
{
    node *y = NULL;
    node *z = t->root;
    while (z != NULL)
    {
        y = z;
        if (x->key < z->key)
            z = z->left;
        else
            z = z->right;
    }
    x->p = y;
    if (y == NULL)
        t->root = x;
    else if (x->key < y->key)
        y->left = x;
    else
        y->right = x;
}

void print(tree *t)
{
    if (t->root == NULL)
    {
        printf("( ) ");
        return;
    }

    printf("( %d ", t->root->key);

    tree left;
    left.root = t->root->left;
    print(&left);

    tree right;
    right.root = t->root->right;
    print(&right);
    printf(") ");
}

void inserthb(tree *t, int a[], int beg, int end)
{
    if (beg <= end)
    {
        int mid = (beg + end) / 2;
        insert(t, create_node(a[mid]));
        inserthb(t, a, beg, mid - 1);
        inserthb(t, a, mid + 1, end);
    }
}
void levelsum(node *r)
{
    node *temp;
    queue q;
    q.head = NULL;
    q.tail = NULL;
    int s = 0;
    if (r == NULL)
    {
        printf("%d", s);
        return;
    }
    enqueue(&q, r);
    enqueue(&q, create_node(-1000001));
    while (queueempty(&q) != -1)
    {
        temp = dequeue(&q);
        if (temp->key == -1000001)
        {
            printf("%d ", s);
            s = 0;
            if (queueempty(&q) != -1)
                enqueue(&q, create_node(-1000001));
        }
        else
        {
            s = s + temp->key;
            if (temp->left != NULL)
                enqueue(&q, temp->left);
            if (temp->right != NULL)
                enqueue(&q, temp->right);
        }
    }
}

int main()
{
    tree t;
    t.root = NULL;
    int n, i;
    scanf("%d", &n);
    int *a;
    a = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    inserthb(&t, a, 0, n - 1);
    print(&t);
    printf("\n");
    levelsum(t.root);
    return 0;
}