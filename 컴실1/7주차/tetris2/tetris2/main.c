//
//  main.c
//  tetris2
//
//  Created by Jeon Charn on 2021/04/24.
//
#define NAMELEN 16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef struct _Node{
    int score;
    char name[NAMELEN];
    struct _Node *nextpoint; // 되는거야 안되는거야,,,
} Node;

Node* headptr = NULL; // 전역변수 headptr
int node_num;

int main() {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

void creatRankList()
{
    int data_num;
    Node* saveptr = NULL;
    FILE* rank = fopen("rank.txt", "r");
    if(fscanf(rank, "%d", &data_num))
    {
        node_num = data_num;
        for(int i=0; i<node_num; i++)
        {
            headptr = (Node*)malloc(sizeof(Node));
            if(i==0)
            {
                saveptr = headptr;
            }
            headptr->nextpoint = NULL;
            fscanf(rank, "%s %d", headptr->name, &(headptr->score));
            headptr = headptr->nextpoint;
        }
        headptr = saveptr;
    }
    else
    {
        node_num = 0;
    }
    fclose(rank);
    
    return;
}

void rank()
{
    clear();
    
    int x, y;
    printw("1. list ranks from X to Y\n");
    printw("2. list ranks by a specific name\n");
    printw("3. delete a specific rank\n");
    switch(getch())
    {
        case '1':
            
    }
}

void writeRankFile(int score) // 끝날 때 score 저장하기,,, 어디에?
{
    char input_name[NAMELEN];
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->nextpoint = NULL;
    printf("please input your name: ");
    scanf("%s", input_name);
    
    new_node->score = score;
    strcpy(new_node->name, input_name);
    Node* headsave = headptr; // 다시 head로 돌아오기 위한 변수
    
    for(int i=1;;i++)
    {
        if(headptr==NULL)
        {
            headptr = new_node;
            break;
        }
        else
        {
            if((headptr->score)<(new_node->score))
            {
                new_node->nextpoint = headptr;
                headptr = new_node;
                break;
            }
            
            else if((headptr->score)==(new_node->score)&&(strcmp(headptr->name, new_node->name)>-1))
            {
                new_node->nextpoint = headptr;
                headptr = new_node;
                break;
            }
        }
        
        if(i!=1)
        {
            headptr = headsave;
        }
    }
    node_num++;
    
    return;
}

void newRank(int score) // 추가만 가능하기 때문에, 문제 0 // 이름이 바뀌었는데???
{
    FILE* rank = fopen("rank.txt", "w");
    fprintf(rank, "%d\n", node_num);
    Node* nowptr = headptr;
    
    for(int i=0; i<node_num; i++)
    {
        fprintf(rank, "%s %d\n", nowptr->name, nowptr->score);
        nowptr = nowptr->nextpoint;
    }
    fclose(rank);
    
    return;
}
