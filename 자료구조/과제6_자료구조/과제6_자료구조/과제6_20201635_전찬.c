//
//  main.c
//  과제6_자료구조
//
//  Created by Jeon Charn on 2021/05/18.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct threadedTree *threadedPointer;
typedef struct threadedTree {
    short int leftThread;
    threadedPointer leftChild;
    char data;
    threadedPointer rightChild;
    short int rightThread;
} threadedTree;

threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);
void insertRight(threadedPointer s, threadedPointer r);
void insertLeft(threadedPointer s, threadedPointer l);
threadedPointer getNewNode(char data);

int main()
{
    
    threadedPointer root = getNewNode('-');
    insertLeft(root, getNewNode('A'));
    insertLeft(root->leftChild, getNewNode('B'));
    insertLeft(root->leftChild->leftChild, getNewNode('D'));
    insertLeft(root->leftChild->leftChild->leftChild,getNewNode('H'));
    insertRight(root->leftChild->leftChild->leftChild,getNewNode('I'));
    insertRight(root->leftChild->leftChild, getNewNode('E'));
    insertRight(root->leftChild, getNewNode('C'));
    insertLeft(root->leftChild->rightChild, getNewNode('F'));
    insertRight(root->leftChild->rightChild, getNewNode('G'));
    tinorder(root);
    
    return 0;
    
}

//inorder의 다음 node를 찾아내기
threadedPointer insucc(threadedPointer tree)
{
    threadedPointer returnval = tree->rightChild;
    
    if(!tree->rightThread)
    {
        while(!returnval->leftThread)
        {
            returnval = returnval->leftChild;
        }
    }
    
    return returnval;
}

//root를 input으로 가지며, node print해주기
void tinorder(threadedPointer tree)
{
    threadedPointer temp = tree;
    while(!temp->leftThread) // leftThread가 1인, inorder에서 첫번째 노드 찾기
    {
        temp = temp->leftChild;
    }
    
    
    for(;;)
    {
        if(temp==tree)
        {
            break;
        }
        //출력 결과의 H가 왼쪽에 붙어 있으므로 -3c 형태로 출력
        printf("%-3c", temp->data);
        temp = insucc(temp);

    }
    printf("\n");
    
    return;
}

void insertRight(threadedPointer s, threadedPointer r)
{
    threadedPointer temp;
    r->rightChild = s->rightChild;
    r->rightThread = s->rightThread;
    r->leftChild = s;
    r->leftThread = 1;
    s->rightChild = r;
    s->rightThread = 0;
    if(!r->rightThread)
    {
        temp = insucc(r);
        temp->leftChild = r;
    }
    
    return;
}

//insertLeft에서 중요한 것은 이미 그 위치에 node가 존재할 경우 존재하는 node 부분의 inorder에서의 마지막 순서인 node를 찾아내기, 이후 그 node의 rightChild에 연결
void insertLeft(threadedPointer s, threadedPointer l)
{
    threadedPointer temp;
    l->leftChild = s->leftChild;
    l->leftThread = s->leftThread;
    l->rightChild = s;
    l->rightThread = 1;
    s->leftChild = l;
    s->leftThread = 0;
    if(!l->leftThread)
    {
        temp = l->leftChild;
        while(!temp->rightThread)
        {
            temp = temp->rightChild;
        }
        //+오른쪽 마지막 node이므로 이미 temp->rightThread = 1일 것!
        temp->rightChild = l;
    }
    
    return;
}

//모든 노드는 아래와 같이 자기 자신을 다시 pointing하는 형태로 만들어짐,, root node의 정의를 위해서 아래와 같이 표현, 이후에 삽입되는 node들은 insert에서 정의해준다.
threadedPointer getNewNode(char data)
{
    threadedPointer newNode = (threadedPointer)malloc(sizeof(threadedTree));
    newNode->data = data;
    newNode->leftChild = newNode;
    newNode->rightChild = newNode;
    newNode->leftThread = 1;
    newNode->rightThread = 1;
    
    return newNode;
}
