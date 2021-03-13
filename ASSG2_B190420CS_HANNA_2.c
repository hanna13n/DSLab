#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    char *word;
    struct node *next;
} node;
typedef struct linkedlist
{
    node *head;
} list;
typedef struct hashtable
{
    list *arr;
    int size;
} hashtable;

node *create_node(char w[])
{
    node *temp;
    temp = (node *)malloc(sizeof(node));
    temp->word = (char *)malloc(strlen(w) * sizeof(char));
    strcpy(temp->word, w);
    temp->next = NULL;
    return temp;
}

void insert(hashtable *t, char w[])
{
    int l = strlen(w);
    int n = (l * l) % t->size;
    if (t->arr[n].head == NULL)
        t->arr[n].head = create_node(w);
    else
    {
        node *p = t->arr[n].head;
        if (strcmp(p->word, w) == 0)
            return;
        while (p->next != NULL && strcmp(p->next->word, w) != 0)
        {
            p = p->next;
        }
        if (p->next == NULL)
            p->next = create_node(w);
        else
            return;
    }
}

void print(hashtable *t)
{
    int i;
    for (i = 0; i < t->size; i++)
    {
        printf("%d:", i);
        if (t->arr[i].head != NULL)
        {
            node *p = t->arr[i].head;
            while (p->next != NULL)
            {
                printf("%s-", p->word);
                p = p->next;
            }
            printf("%s\n", p->word);
        }
        else
            printf("null\n");
    }
}

int main()
{
    int k, i, j = 0;

    scanf("%d\n", &k);

    hashtable t;
    t.size = k;
    t.arr = (list *)malloc(k * sizeof(list));

    for (i = 0; i < k; i++)
        t.arr[i].head = NULL;

    char str[501], w[501];
    scanf("%[^\n]%*c", str);

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ')
        {
            w[j] = str[i];
            j++;
        }
        else
        {
            w[j] = '\0';
            insert(&t, w);
            j = 0;
        }
    }
    w[j] = '\0';
    insert(&t, w);

    print(&t);

    return 0;
}