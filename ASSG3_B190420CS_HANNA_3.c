#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
    int key;
    char color;
    struct node *left, *right;
} node;

typedef struct rbtree
{
    node *root;
} tree;

node *create_node(int k)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->key = k;
    temp->color = 'R';
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

node *rotatefromleft(node *n)
{
    node *p = n->left;
    n->left = p->right;
    p->right = n;
    return p;
}

node *rotatefromright(node *n)
{
    node *p = n->right;
    n->right = p->left;
    p->left = n;
    return p;
}

node *insertredblack(node *r, node *x)
{
    if (r == NULL)
        return x;

    if (r->key < x->key)
    {
        r->right = insertredblack(r->right, x);
        if (r->right->color == 'B')
            return r;
        else
        {
            if ((r->right->left != NULL && r->right->left->color == 'R') || (r->right->right != NULL && r->right->right->color == 'R'))
            {
                if (r->left != NULL && r->left->color == 'R')
                {
                    r->left->color = 'B';
                    r->right->color = 'B';
                    r->color = 'R';
                    return r;
                }
                else
                {
                    if (r->right->left != NULL && r->right->left->color == 'R')
                        r->right = rotatefromleft(r->right);
                    node *y = rotatefromright(r);
                    y->left->color = 'R';
                    y->color = 'B';
                    return y;
                }
            }
            else
                return r;
        }
    }
    else
    {
        r->left = insertredblack(r->left, x);
        if (r->left->color == 'B')
            return r;
        else
        {
            if ((r->left->left != NULL && r->left->left->color == 'R') || (r->left->right != NULL && r->left->right->color == 'R'))
            {
                if (r->right->color == 'R')
                {
                    r->right->color = 'B';
                    r->left->color = 'B';
                    r->color = 'R';
                    return r;
                }
                else
                {
                    if (r->left->right != NULL && r->left->right->color == 'R')
                        r->left = rotatefromright(r->left);
                    node *y = rotatefromleft(r);
                    y->right->color == 'R';
                    y->color = 'B';
                    return y;
                }
            }
            else
                return r;
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

    printf("( %d %c ", t->root->key, t->root->color);

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
    tree *t = (tree *)malloc(sizeof(tree));
    t->root = NULL;
    int k;
    char ch;
    scanf("%d", &k);
    ch = getc(stdin);
    while (ch == '\n')
    {
        t->root = insertredblack(t->root, create_node(k));
        if (t->root->color == 'R')
            t->root->color = 'B';
        print(t);
        printf("\n");
        scanf("%d", &k);
        ch = getc(stdin);
    }

    return 0;
}