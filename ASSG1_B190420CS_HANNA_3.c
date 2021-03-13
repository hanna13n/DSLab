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

int add(node *r)
{
    if (r == NULL)
        return 0;
    else
        return r->key + add(r->left) + add(r->right);
}

int isbst(node *r, int *p)
{
    if (r == NULL)
        return 1;
    if (!isbst(r->left, p))
        return 0;
    if (r->key < *p)
        return 0;
    *p = r->key;
    return isbst(r->right, p);
}

int c = 0;
void countbst(tree *t, int k)
{
    if (t->root == NULL)
        return;
    int p = -1;

    if (isbst(t->root, &p) == 1 && add(t->root) == k)
        c++;

    tree left;
    left.root = t->root->left;
    countbst(&left, k);

    tree right;
    right.root = t->root->right;
    countbst(&right, k);
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
    countbst(&t, x);
    if (c == 0)
        printf("%d", -1);
    else
    {
        printf("%d", c);
    }

    return 0;
}