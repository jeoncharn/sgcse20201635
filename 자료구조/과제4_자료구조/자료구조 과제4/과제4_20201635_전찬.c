//
//  main.c
//  자료구조 과제3
//
//  Created by Jeon Charn on 2021/04/29.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Node *nodepointer; // pointer형을 정의
typedef struct Node{
    int data;
    nodepointer nextpoint;
} Node;

void pushstack(nodepointer* top, int data);
void pushqueue(nodepointer* front, nodepointer* rear, int data);
void popstack(nodepointer* top);
void popqueue(nodepointer* front);
void printLinkedList(nodepointer first);

int main() {
    
    nodepointer stack_top = NULL; // stack의 맨 앞 node를 pointing
    nodepointer queue_front = NULL; // queue의 맨 앞 node를 pointing
    nodepointer queue_rear = NULL; // queue의 맨 뒤 node를 pointing
    
    int act; // 0 또는 1을 파일에서 받아오는 변수
    int data;
    
    FILE* data_file = fopen("input.txt", "r");
    while(1)
    {
        if(fscanf(data_file, "%d", &act)==EOF)
        {
            break;
        }
        
        if(act==0)
        {
            fscanf(data_file, "%d\n", &data);
            pushstack(&stack_top, data);
            pushqueue(&queue_front, &queue_rear, data);
        }
        
        else
        {
            popstack(&stack_top);
            popqueue(&queue_front);
        }
        
    }
    //printf("The stack result is: ");
    printLinkedList(stack_top);
    //printf("The queue result is: ");
    printLinkedList(queue_front);
    
    return 0;
}


void pushstack(nodepointer* top, int data)
{
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    newnode->nextpoint = *top;
    *top = newnode;
    
    return;
}

void pushqueue(nodepointer* front, nodepointer* rear, int data)
{
    Node* newnode = (Node*)malloc(sizeof(Node));
    newnode->data = data;
    newnode->nextpoint = NULL; // 마지막에 들어가기 때문에 무조건 NULL 이다.
    
    if(*front==NULL) // queue가 empty list인 경우에
    {
        *front = newnode;
    }
    else
    {
        (*rear)->nextpoint = newnode;
    }
    
    *rear = newnode;
    
    return;
}

void popstack(nodepointer* top)
{
    if(*top==NULL) // 이미 비어있는 경우
    {
        printf("stack is already empty!\n");
        return; // exit을 하지 않은 이유는 popqueue() 에서의 printf도 수행하기 위해서이다. 추가로 stack이 empty이면 queue도 empty이다.
    }
    else
    {
        Node* save = *top;
        *top = (*top)->nextpoint;
        free(save);
    }
    
    return;
}

void popqueue(nodepointer* front) // 사실상 popstack과 동일한 수행을 하지만, 쉽게 구분할 수 있도록 사용
{
    if(*front==NULL) // 이미 비어있는 경우
    {
        printf("queue is already empty!\n");
        exit(1);
    }
    else
    {
        Node* save = *front;
        *front = (*front)->nextpoint;
        free(save);
    }
    
    return;
}

void printLinkedList(nodepointer first) // stack, queue 모두 linked list이기 때문에 하나의 함수로 구현가능
{
    Node* save;
    while(1)
    {
        if(first==NULL)
        {
            break;
        }
        printf("%d ", first->data);
        
        save = first;
        free(save); // print해주며 동적할당 해제해주기
        
        first = first->nextpoint;
    }
    printf("\n");
    
    return;
}
