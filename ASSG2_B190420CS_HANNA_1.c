#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

typedef struct node
{
    int product_id;
} node;

node *create_node(int k)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->product_id = k;
    return temp;
}

typedef struct hash_table
{
    node **products;
    int size;
} table;

table *hashtable(int m)
{
    table *t = (table *)malloc(sizeof(table));
    t->size = m;
    t->products = (node **)malloc(m * sizeof(node *));

    int i;
    for (i = 0; i < m; i++)
        t->products[i] = NULL;

    return t;
}
int isprime(int n)
{
    int i, flag = 0;

    for (i = 2; i <= n / 2; i++)
    {
        if ((n % i) == 0)
        {
            flag++;
            break;
        }
    }
    if (flag == 0)
        return 1;
    else
        return -1;
}
int nearprime(int n)
{
    int i;
    for (i = n - 1; i >= 2; i--)
    {
        if (isprime(i) == 1)
            break;
    }
    return i;
}
char type;
int c1, c2, r;
void insert(table *t, int k)
{
    int i = 0, h;
    h = k % t->size;
    if (type == 'a')
    {
        while (i < t->size && t->products[h] != NULL)
        {
            i++;
            h = ((k % t->size) + c1 * i + c2 * i * i) % t->size;
        }

        t->products[h] = create_node(k);
    }
    else
    {
        while (i < t->size && t->products[h] != NULL)
        {
            i++;
            h = ((k % t->size) + i * (r - (k % r))) % t->size;
        }

        t->products[h] = create_node(k);
    }
}
node *search(table *t, int k)
{
    int i = 0, h;
    h = k % t->size;
    if (type == 'a')
    {
        while (i < t->size)
        {
            if (t->products[h] != NULL && t->products[h]->product_id == k)
                break;
            i++;
            h = ((k % t->size) + c1 * i + c2 * i * i) % t->size;
        }
        if (i < t->size)
            return t->products[h];
        else
            return NULL;
    }
    else
    {
        while (i < t->size)
        {
            if (t->products[h] != NULL && t->products[h]->product_id == k)
                break;
            i++;
            h = ((k % t->size) + i * (r - (k % r))) % t->size;
        }
        if (i < t->size)
            return t->products[h];
        else
            return NULL;
    }
}
void delete_(table *t, int k)
{
    int i = 0, h;
    h = k % t->size;
    if (type == 'a')
    {
        while (i < t->size)
        {
            if (t->products[h] != NULL && t->products[h]->product_id == k)
                break;
            i++;
            h = ((k % t->size) + c1 * i + c2 * i * i) % t->size;
        }
        t->products[h] = NULL;
    }
    else
    {
        while (i < t->size)
        {
            if (t->products[h] != NULL && t->products[h]->product_id == k)
                break;
            i++;
            h = ((k % t->size) + i * (r - (k % r))) % t->size;
        }
        t->products[h] = NULL;
    }
}
void print(table *t)
{
    int i;
    for (i = 0; i < t->size; i++)
    {
        printf("%d ", i);
        if (t->products[i] != NULL)
            printf("(%d)\n", t->products[i]->product_id);
        else
            printf("()\n");
    }
}
int main()
{
    int m, x;
    char ch;
    node *n;
    scanf("%c\n", &type);
    scanf("%d\n", &m);
    table *t = hashtable(m);
    if (type == 'a')
    {
        scanf("%d %d\n", &c1, &c2);
    }
    else
    {
        r = nearprime(m);
    }
menu:
    scanf("%c", &ch);
    switch (ch)
    {
    case 'i':
        scanf("%d", &x);
        insert(t, x);
        break;
    case 's':
        scanf("%d", &x);
        n = search(t, x);
        if (n == NULL)
            printf("%d\n", -1);
        else
            printf("%d\n", 1);
        break;
    case 'd':
        scanf("%d", &x);
        delete_(t, x);
        break;
    case 'p':
        print(t);
        break;
    case 't':
        exit(0);
    }
    goto menu;
    return 0;
}