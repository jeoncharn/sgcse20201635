#include <stdio.h>
#include <stdlib.h>


typedef struct node* sptr;

typedef struct {
    int count;
    sptr link;
} STACK;

typedef struct node {
    int data;
    sptr link;
}STACK_NODE;

void Exit(STACK* a);
void Push(STACK* a);
void Pop(STACK* a);
void PrintAll(STACK a);

int main()
{
    int select;
    STACK* head;
    
    head = (STACK*)malloc(sizeof(STACK));
    head->count = 0;
    head->link = NULL;
    
    printf("----- Menu -----\n");
    printf("- 0 : Exit\n");
    printf("- 1 : Push\n");
    printf("- 2 : Pop\n");
    printf("- 3 : Print All\n");

    while(1)
    {
        printf("\nSelect > ");

        scanf("%d", &select);

        if(select == 0)
        {
            Exit(head);
            break;
        }
        else if(select == 1)
        {
            Push(head);
        }
        else if(select == 2)
        {
            Pop(head);
        }
        else
        {
            PrintAll(*head);
        }
    }
    
    return 0;
}

void Exit(STACK* a)
{
    for(int i=0; i<(a->count); i++)
    {
        sptr link_node = a->link;
        for(int j=0; j<(a->count)-i-1; j++)
        {
            link_node = link_node->link;
        }
        free(link_node);
    }
    
    return;
}

void Push(STACK* a)
{
    sptr new;
    sptr link_node;
    int input;
    new = (sptr)malloc(sizeof(STACK_NODE));
    
    printf("Input Data > ");
    scanf("%d", &input);
    
    if(a->count == 0)
    {
        a->link = new;
        new->data = input;
    }
    else
    {
        link_node = a->link;
        for(int i=0; i<(a->count-1); i++)
        {
            link_node = link_node->link;
        }
        link_node->link = new;
        new->data = input;
    }
    (a->count)++;
    
    return;
}

void Pop(STACK* a)
{
    sptr link_node = (a->link);
    if(a->count == 1)
    {
        printf("Pop %d\n", link_node->data);
        free(a->link);
        a->link = NULL;
    }
    else
    {
        for(int i=0;i<(a->count-2); a++)
        {
            link_node = link_node->link;
        }
       printf("Pop %d\n", ((link_node->link)->data));
        free(link_node->link);
        link_node->link = NULL;
    }
    (a->count)--;
    return;
}

void PrintAll(STACK a)
{
    sptr link_node = a.link;
    for(int i=0; i<a.count; i++)
    {
        printf("%d ", link_node->data);
        link_node = link_node->link;
    }
    printf("\n");
    printf("Stack Level : %d\n", a.count);
    
    return;
}