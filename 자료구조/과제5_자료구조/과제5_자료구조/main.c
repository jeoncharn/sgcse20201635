//
//  main.c
//  과제5_자료구조
//
//  Created by Jeon Charn on 2021/05/08.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node* nextpointer;
typedef struct _Node {
    int data;
    nextpointer next;
} Node;

Node* makeCircularList(char* filename);
void addTwoList(nextpointer* head_a, nextpointer* head_b);
void printList(nextpointer head);
void deleteFromList(nextpointer* head, char* filename);
void freeList(nextpointer head);

int main()
{
    nextpointer headof_lista;
    nextpointer headof_listb;
    
    headof_lista = makeCircularList("A.txt");
    headof_listb = makeCircularList("B.txt");
    
    //printList(headof_lista); //lista 테스트
    //printList(headof_listb); //listb 테스트
    addTwoList(&headof_lista, &headof_listb);
    printList(headof_lista);
    
    deleteFromList(&headof_lista, "C.txt");
    printList(headof_lista);
    
    freeList(headof_lista);
    return 0;
}


Node* makeCircularList(char* filename)
{
    nextpointer head_pointer = NULL;
    nextpointer save_head = NULL;
    int data;
    FILE* file = fopen(filename, "r");
    
    while(fscanf(file, "%d\n", &data)!=EOF)
    {
        if(head_pointer == NULL)
        {
            head_pointer = (Node*)malloc(sizeof(Node));
            head_pointer->data = data;
            save_head = head_pointer;
            
        }
        else
        {
            head_pointer->next = (Node*)malloc(sizeof(Node));
            head_pointer = head_pointer->next;
            head_pointer->data = data;
        }
    }
    head_pointer->next = save_head;
    
    fclose(file);
    
    return save_head;
}

void addTwoList(nextpointer* head_a, nextpointer* head_b)
{
    if(*head_a==NULL&&*head_b==NULL)
    {
        printf("A.txt and B.txt is empty!\n");
        // exit(1);
    }
    
    else if(*head_a==NULL)
    {
        printf("A.txt is empty.\n");
        *head_a = *head_b;
    }
    
    else if(*head_b==NULL)
    {
        printf("B.txt is empty.\n");
    }
    
    else
    {
        nextpointer search = *head_a;
        do
        {
            search = search->next;
        } while(search->next!=*head_a);
        
        search->next = *head_b;
        
        search = *head_b;
        do
        {
            search = search->next;
        } while(search->next!=*head_b);
        search->next = *head_a;
    }
    
    return;
}

void printList(nextpointer head)
{
    nextpointer save = head;
    do
    {
        printf("%d ", head->data);
        head = head->next;
    } while(head!=save);
    printf("\n");
    
    return;
}

void deleteFromList(nextpointer* head, char* filename)
{
    int delete_data;
    Node* fakenode = (Node*)malloc(sizeof(Node));
    fakenode->next = *head;
    while((*head)->next!=(fakenode->next))
    {
        *head = (*head)->next;
    }
    (*head)->next = fakenode; // fake를 linked list 맨 앞에 넣어준다.
    
    FILE* delete_file = fopen(filename, "r");
    
    while(fscanf(delete_file, "%d\n", &delete_data)!=EOF)
    {
        Node* save = fakenode;
        do
        {
            if((save->next)->data==delete_data)
            {
                Node* free_variable = save->next;
                save->next = save->next->next;
                free(free_variable);
            }
            else
            {
                save = save->next;
            }
        } while(save->next!=fakenode);
    }
    fclose(delete_file);
    
    if(fakenode->next==fakenode) //모든 노드를 삭제할 경우
    {
        printf("All node deleted!\n");
        exit(1);
    }
    
    *head = fakenode->next;
    while((*head)->next!=fakenode)
    {
        *head = (*head)->next;
    }
    (*head)->next = fakenode->next;
    *head = (*head)->next;
    
    free(fakenode);
    
    return;
}

void freeList(nextpointer head)
{
    Node* save = head;
    Node* free_data;
    do
    {
        free_data = head;
        head = head->next;
        free(free_data);
    } while(head!=save);
    
    return;
}
