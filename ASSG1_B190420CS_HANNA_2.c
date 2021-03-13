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
int flag = 0;
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

void exptotree(tree *t, char *s)
{
    int i = 0, n, neg = 0;
    node *k;
    while (s[i] != '\0')
    {

        if (s[i] == '(')
        {
            i += 2;
            if (isdigit(s[i]) || s[i] == '-')
            {
                neg = 0;
                if (s[i] == '-')
                {
                    i++;
                    neg++;
                }
                n = 0;
                while (isdigit(s[i]))
                {
                    n = n * 10 + (int)(s[i] - '0');
                    i++;
                }
                i++;
                if (neg != 0)
                    n = n * -1;
                if (t->root == NULL)
                {
                    t->root = create_node(n);
                    k = t->root;
                }
                else if (k->left == NULL)
                {
                    k->left = create_node(n);
                    k->left->p = k;
                    k = k->left;
                }
                else if (k->right == NULL)
                {
                    k->right = create_node(n);
                    k->right->p = k;
                    k = k->right;
                }
            }
            else if (s[i] == ')' && s[i - 4] != ')')
            {
                k->left = NULL;
                i += 2;
                if (isdigit(s[i + 2]) || s[i + 2] == '-')
                {
                    neg = 0;
                    i += 2;
                    if (s[i] == '-')
                    {
                        i++;
                        neg++;
                    }
                    n = 0;
                    while (isdigit(s[i]))
                    {
                        n = n * 10 + (int)(s[i] - '0');
                        i++;
                    }
                    i++;
                    if (neg != 0)
                        n = n * -1;
                    k->right = create_node(n);
                    k->right->p = k;
                    k = k->right;
                }
            }
            else if (s[i] == ')' && s[i - 4] == ')')
            {
                k->right = NULL;
                i += 2;
            }
        }
        else if (s[i] == ')')
        {
            k = k->p;
            i += 2;
        }
    }
}

int getlevel(node *x, int k, int l)
{
    if (x == NULL)
        return -1;
    if (x->key == k)
        return l;

    int p = getlevel(x->left, k, l + 1);
    if (p != -1)
        return p;
    p = getlevel(x->right, k, l + 1);
    return p;
}

int level(tree *t, int k)
{
    return getlevel(t->root, k, 1);
}

node *search(node *x, int k)
{
    if (x == NULL)
        return NULL;
    if (x->key == k)
        return x;

    node *p = search(x->left, k);
    if (p != NULL)
        return p;
    p = search(x->right, k);
    return p;
}

void levelcousins(node *r, node *x, int l)
{
    if (r == NULL || l < 2)
    {
        printf("%d ", -1);
        flag++;
        return;
    }
    if (l == 2)
    {

        if (r->left != NULL && x->p != r)
        {
            printf("%d ", r->left->key);
            flag++;
        }
        if (r->right != NULL && x->p != r)
        {
            printf("%d ", r->right->key);
            flag++;
        }
    }
    else if (l > 2)
    {
        levelcousins(r->left, x, l - 1);
        levelcousins(r->right, x, l - 1);
    }
}

void printcousins(tree *t, int k)
{
    int l = level(t, k);
    node *x = search(t->root, k);
    if (l == 2)
    {
        printf("%d ", -1);
        return;
    }
    flag = 0;
    levelcousins(t->root, x, l);
    if (flag == 0)
        printf("%d ", -1);
}

int main()
{
    tree t;
    t.root = NULL;

    int x;
    char exp[1000000];
    scanf("%[^\n]%*c", exp);
    scanf("%d", &x);
    exptotree(&t, exp);
    printcousins(&t, x);

    return 0;
}