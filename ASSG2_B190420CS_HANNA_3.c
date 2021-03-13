#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct node
{
    char *string;
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
    temp->string = (char *)malloc(strlen(w) * sizeof(char));
    strcpy(temp->string, w);
    temp->next = NULL;
    return temp;
}

void insert(hashtable *t, char str[])
{
    int x = 0, j, i;
    int flag[8] = {0};

    for (j = 0; str[j] != '\0'; j++)
    {
        switch (str[j])
        {
        case 'a':
            if (flag[0] == 0)
            {
                x = x + pow(2, 0);
                flag[0]++;
            }
            break;
        case 'b':
            if (flag[1] == 0)
            {
                x = x + pow(2, 1);
                flag[1]++;
            };
            break;
        case 'c':
            if (flag[2] == 0)
            {
                x = x + pow(2, 2);
                flag[2]++;
            }
            break;
        case 'd':
            if (flag[3] == 0)
            {
                x = x + pow(2, 3);
                flag[3]++;
            }
            break;
        case 'e':
            if (flag[4] == 0)
            {
                x = x + pow(2, 4);
                flag[4]++;
            }
            break;
        case 'f':
            if (flag[5] == 0)
            {
                x = x + pow(2, 5);
                flag[5]++;
            }
            break;
        case 'g':
            if (flag[6] == 0)
            {
                x = x + pow(2, 6);
                flag[6]++;
            }
            break;
        case 'h':
            if (flag[7] == 0)
            {
                x = x + pow(2, 7);
                flag[7]++;
            }
            break;
        }
        if (x == 255)
        {
            x = x % 255;
            break;
        }
    }

    if (t->arr[x].head == NULL)
        t->arr[x].head = create_node(str);

    else
    {
        node *p = t->arr[x].head;
        if (strcmp(p->string, str) != 0)
        {
            i = 0;
            while (str[i] != '\0' && p->string[i] != '\0' && str[i] == p->string[i])
            {
                i++;
            }
            if (str[i] < p->string[i])
            {
                node *z = create_node(str);
                z->next = p;
                t->arr[x].head = z;
            }
            else
            {
                while (p->next != NULL && strcmp(p->next->string, str) != 0)
                {
                    i = 0;
                    while (str[i] != '\0' && (p->next->string[i] != '\0') && str[i] == p->next->string[i])
                    {
                        i++;
                    }
                    if (str[i] < p->next->string[i])
                    {
                        node *z = create_node(str);
                        z->next = p->next;
                        p->next = z;
                        return;
                    }
                    p = p->next;
                }
                if (p->next == NULL)
                    p->next = create_node(str);
            }
        }
    }
}

int main()
{
    int n, i;
    hashtable t;
    t.size = 255;
    t.arr = (list *)malloc(255 * sizeof(list));
    for (i = 0; i < 255; i++)
        t.arr[i].head = NULL;

    scanf("%d\n", &n);

    char str[51];
    for (i = 0; i < n; i++)
    {
        scanf("%s", str);
        insert(&t, str);
    }

    for (i = 1; i < 255; i++)
    {
        if (t.arr[i].head != NULL)
        {
            node *p = t.arr[i].head;
            while (p->next != NULL)
            {
                printf("%s ", p->string);
                p = p->next;
            }
            printf("%s\n", p->string);
        }
    }
    if (t.arr[0].head != NULL)
    {
        node *p = t.arr[0].head;
        while (p->next != NULL)
        {
            printf("%s ", p->string);
            p = p->next;
        }
        printf("%s\n", p->string);
    }

    return 0;
}