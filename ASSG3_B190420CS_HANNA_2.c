#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
    int key;
    int count;
    int h;
    struct node *left, *right;
} node;
typedef struct avltree
{
    node *root;
} tree;
node *create_node(int k)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->key = k;
    temp->h = 0;
    temp->count = 1;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
int height(node *n)
{
    if (n == NULL)
        return -1;
    else
        return n->h;
}
int max(int a, int b)
{
    return a > b ? a : b;
}
node *rotatefromleft(node *n)
{
    node *p = n->left;
    n->left = p->right;
    p->right = n;
    n->h = max(height(n->left), height(n->right)) + 1;
    p->h = max(height(p->left), height(p->right)) + 1;
    return p;
}
node *rotatefromright(node *n)
{
    node *p = n->right;
    n->right = p->left;
    p->left = n;
    n->h = max(height(n->left), height(n->right)) + 1;
    p->h = max(height(p->left), height(p->right)) + 1;
    return p;
}
node *doublerotatefromright(node *n)
{
    n->right = rotatefromleft(n->right);
    return rotatefromright(n);
}
node *doublerotatefromleft(node *n)
{
    n->left = rotatefromright(n->left);
    return rotatefromleft(n);
}
int getbalance(node *a)
{
    if (a == NULL)
        return -2;
    return height(a->left) - height(a->right);
}
node *insert(node *a, int k)
{
    if (a == NULL)
        return create_node(k);
    else
    {
        if (a->key == k)
        {
            a->count++;
            return a;
        }
        else if (a->key > k)
        {
            a->left = insert(a->left, k);
            if (abs(getbalance(a)) == 2)
            {
                if (a->left->key > k)
                    a = rotatefromleft(a);
                else
                    a = doublerotatefromleft(a);
            }
        }
        else if (a->key < k)
        {
            a->right = insert(a->right, k);
            if (abs(getbalance(a)) == 2)
            {
                if (a->right->key < k)
                    a = rotatefromright(a);
                else
                    a = doublerotatefromright(a);
            }
        }
        a->h = max(height(a->left), height(a->right)) + 1;
        return a;
    }
}

void inorder(tree *t)
{
    if (t->root == NULL)
        return;

    tree left;
    left.root = t->root->left;
    inorder(&left);

    int i;
    for (i = 0; i < t->root->count; i++)
        printf("%d ", t->root->key);

    tree right;
    right.root = t->root->right;
    inorder(&right);
}
int main()
{
    int n, x, i;
    tree *a = (tree *)malloc(sizeof(tree));
    a->root = NULL;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &x);
        a->root = insert(a->root, x);
    }
    inorder(a);
}