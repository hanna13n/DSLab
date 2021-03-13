#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

void insert(tree *t, int k)
{
    queue q;
    node *temp;
    q.head = NULL;
    q.tail = NULL;

    if (t->root == NULL)
    {
        t->root = create_node(k);
        return;
    }

    enqueue(&q, t->root);
    while (queueempty(&q) != -1)
    {
        temp = dequeue(&q);
        if (temp->left != NULL)
            enqueue(&q, temp->left);
        else
        {
            temp->left = create_node(k);
            temp->left->p = temp;
            return;
        }
        if (temp->right != NULL)
        {
            enqueue(&q, temp->right);
        }
        else
        {
            temp->right = create_node(k);
            temp->right->p = temp;
            return;
        }
    }
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
int main()
{
    tree t;
    t.root = NULL;
    char ch;
    int k;
menu:
    scanf("%c", &ch);

    switch (ch)
    {
    case 'i':
        scanf("%d", &k);
        insert(&t, k);
        break;
    case 'p':
        print(&t);
        break;
    case 'e':
        exit(0);
    }

    goto menu;

    return 0;
}
