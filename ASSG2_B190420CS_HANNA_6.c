#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left, *right;
} node;

typedef struct tree
{
    node *root;
} tree;

node *create_node(int k)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = k;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void insert(tree *t, node *x)
{
    node *y = NULL;
    node *z = t->root;
    while (z != NULL)
    {
        y = z;
        if (x->data < z->data)
            z = z->left;
        else
            z = z->right;
    }
    if (y == NULL)
        t->root = x;
    else if (x->data < y->data)
        y->left = x;
    else
        y->right = x;
}

int maxinpath(node *p, int x)
{
    node *z = p;
    int max = -1000001;
    while (z->data != x)
    {
        if (z->data > max)
            max = z->data;

        if (z->data > x)
            z = z->left;
        else
            z = z->right;
    }
    return max;
}

int maxelement(tree *t, int x, int y)
{
    node *r = t->root;
    while ((x < r->data && y < r->data) || (x > r->data && y > r->data))
    {
        if (x < r->data && y < r->data)
            r = r->left;

        else if (x >= r->data && y >= r->data)
            r = r->right;
    }

    if ((r->data == x) || (r->data == y))
    {
        if ((x > y && r->data == x) || (x < y && r->data == y))
        {
            r = r->left;
            if (x > y)
                return maxinpath(r, y);
            else
                return maxinpath(r, x);
        }
        else
        {
            r = r->right;
            if (x > y)
                return maxinpath(r, x);
            else
                return maxinpath(r, y);
        }
    }

    else
    {
        int p = maxinpath(r, x), q = maxinpath(r, y);
        if (p > q)
            return p;
        else
            return q;
    }
}

int main()
{
    int arr[1000001], i = 0, n, a, b;
    tree t;
    t.root = NULL;
    char temp;
    do
    {
        scanf("%d%c", &arr[i], &temp);
        i++;
    } while (temp != '\n');
    n = i;

    for (i = 0; i < n; i++)
        insert(&t, create_node(arr[i]));

    scanf("%d %d", &a, &b);
    printf("%d\n", maxelement(&t, a, b));
    return 0;
}