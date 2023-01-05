#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_Node(int id, char* name);

typedef struct _Node{
    int StudentID;
    char StudentName[40];
    struct _Node *nptr;
} Node;

Node* head = NULL;

int main()
{
    int menu, id;
    Node* lastptr;
    char name[40];
    
    printf("[Select Menu]\n");
    printf("1 Insert a new student\n");
    printf("2 Print list\n");
    
    while(1)
    {
        scanf("%d", &menu);
        
        if(menu==1)
        {
            printf("Enter a student: ");
            scanf("%d/%s", &id, name);
            create_Node(id, name);
        }
        
        else
        {
            lastptr = head;
            while(lastptr!=NULL)
            {
                printf("[%d/%s]", lastptr->StudentID, lastptr->StudentName);
                printf(" -> ");
                
                lastptr = (lastptr->nptr);
            }
            
            printf("NULL\n");
        }
    }
}

void create_Node(int id, char* name)
{
    Node* new;
    Node* lptr;
	Node* save;
    
    new = (Node*)malloc(sizeof(Node));
    
    new->StudentID = id;
    strcpy((new->StudentName), name);
    
    if(head==NULL)
    {
        head = new;
        (new->nptr) = NULL;
    }
    
    else
    {
        lptr = head;
        while(lptr!=NULL)
        {
            save = lptr;
			lptr = (lptr->nptr);
        }
        (save->nptr) = new;
        (new->nptr) = NULL;
    }
    
    return;
}
