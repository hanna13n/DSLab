#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef struct node
{
    int key;
    struct node *left, *right;
} node;

typedef struct tree
{
    node *root;
} tree;

node *create_node(int k)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->key = k;
    temp->left = NULL;
    temp->right = NULL;
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
                    k = k->left;
                }
                else if (k->right == NULL)
                {
                    k->right = create_node(n);
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
            if (t->root != NULL)
            {
                node *r = t->root;
                if (r == k)
                    return;
                while (r != NULL)
                {
                    if (k == r->left || k == r->right)
                    {
                        k = r;
                        break;
                    }
                    if (k->key < r->key)
                        r = r->left;
                    else if (k->key > r->key)
                        r = r->right;
                }
            }
            i += 2;
        }
    }
}

node *minvalue(node *x)
{
    while (x->left != NULL)
        x = x->left;
    return x;
}

node *maxvalue(node *x)
{
    while (x->right != NULL)
    {
        x = x->right;
    }
    return x;
}

node *search(tree *t, int k)
{
    node *x = t->root;
    while (x != NULL && k != x->key)
    {
        if (k < x->key)
            x = x->left;
        else
            x = x->right;
    }
    return x;
}

node *predecessor(tree *t, int y)
{
    node *x = search(t, y);
    if (x == NULL)
        return NULL;
    if (x->left != NULL)
        return maxvalue(x->left);
    node *z = NULL;
    node *r = t->root;
    while (r != NULL)
    {
        if (y > r->key)
        {
            z = r;
            r = r->right;
        }
        else if (y < r->key)
            r = r->left;
        else
            break;
    }
    return z;
}

node *successor(tree *t, int y)
{
    node *x = search(t, y);
    if (x == NULL)
        return NULL;
    if (x->right != NULL)
        return minvalue(x->right);
    node *z = NULL;
    node *r = t->root;
    while (r != NULL)
    {
        if (y < r->key)
        {
            z = r;
            r = r->left;
        }
        else if (y > r->key)
            r = r->right;
        else
            break;
    }
    return z;
}
int c;
node *ksmallest(tree *t, int k)
{
    if (t->root == NULL)
        return NULL;
    tree left;
    left.root = t->root->left;
    node *l = ksmallest(&left, k);
    if (l != NULL)
        return l;
    if (++c == k)
        return t->root;

    tree right;
    right.root = t->root->right;
    return ksmallest(&right, k);
}

node *klargest(tree *t, int k)
{
    if (t->root == NULL)
        return NULL;
    tree right;
    right.root = t->root->right;
    node *r = klargest(&right, k);
    if (r != NULL)
        return r;
    if (++c == k)
        return t->root;
    tree left;
    left.root = t->root->left;
    return klargest(&left, k);
}

void inorder(tree *t)
{
    if (t->root == NULL)
        return;

    tree left;
    left.root = t->root->left;
    inorder(&left);

    printf("%d ", t->root->key);

    tree right;
    right.root = t->root->right;
    inorder(&right);
}
int main()
{
    tree t;
    t.root = NULL;
    char exp[1000000];
    scanf("%[^\n]%*c", exp);
    exptotree(&t, exp);

    node *n;
    int x;
    char ch;
menu:
    scanf("%c", &ch);
    switch (ch)
    {
    case 'r':
        scanf("%d", &x);
        n = predecessor(&t, x);
        if (n == NULL)
            printf("%d\n", -1);
        else
            printf("%d\n", n->key);
        break;
    case 'u':
        scanf("%d", &x);
        n = successor(&t, x);
        if (n == NULL)
            printf("%d\n", -1);
        else
            printf("%d\n", n->key);
        break;
    case 'i':
        inorder(&t);
        printf("\n");
        break;
    case 'l':
        scanf("%d", &x);
        c = 0;
        n = klargest(&t, x);
        if (n == NULL)
            printf("%d\n", -1);
        else
            printf("%d\n", n->key);
        break;
    case 's':
        scanf("%d", &x);
        c = 0;
        n = ksmallest(&t, x);
        if (n == NULL)
            printf("%d\n", -1);
        else
            printf("%d\n", n->key);
        break;
    case 'e':
        exit(0);
    }
    goto menu;
    return 0;
}