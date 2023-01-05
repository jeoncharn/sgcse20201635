//
//  main.c
//  tree_implementation
//
//  Created by Jeon Charn on 2021/05/04.
//

#include <stdio.h>
#include <stdlib.h>
#define BLOCK_NUM 3

typedef struct _RecNode{
    int level,accumulatedScore;
    char recField[HEIGHT][WIDTH];
    int recBlockID, recBlockX,recBlockY,recBlockRotate;
    struct _RecNode *c[CHILDREN_MAX];
} RecNode;


//그놈의 주소를 받았을 때, 그놈의 주소에 있는 놈들을 malloc 하고, 정보를 저장해야 한다. 이걸 또 반복해야 되는디,,,

void recommend(Node* root)
{
    if(root->level == BLOCK_NUM)
    {
        if(root->accumulatedScore>maxscore)
        {
            recommendR = root->recBlockRotate;
            recommendY = root->recBlockY;
            recommendX = root->recBlockX;
        }
        return;
        
    }
    else
    {
        int count = 0;
        for(int rotate = 0; rotate<4; rotate++)
        {
            for(int xposition = -2; xposition<10; xposition++)
            {
                if(ChecktoMove(root->recField, nextBlock[root->level], rotate, -1, xposition))
                {
                    
                    root->c[count] = (Node*)malloc(sizeof(Node));
                    root->c[count]->level = root->level + 1;
                    root->c[count]->recBlockID = nextBlock[root->level];
                    root->c[count]->recBlockX = xposition;
                    int yposition = 0;
                    while(ChecktoMove(root->recField, nextBlock[root->level], rotate, yposition, xposition))
                    {
                        yposition++;
                    }
                    yposition--;
                    
                    root->c[count]->recBlockY = yposition;
                    root->c[count]->recBlockRotate = rotate;
                    
                    for(int i=0; i<HEIGHT; i++)
                    {
                        for(int j=0; j<WIDTH; j++)
                        {
                            root->c[count]->recField[i][j] = root->recField[i][j];
                        }
                    }
                    root->c[count]->accumulatedScore = root->accumulatedScore + 100*AddBlockToField(root->c[count]->recField, root->c[count]->recBlockID, root->c[count]->recBlockRotate, root->c[count]->recBlockY, root->c[count]->recBlockX);
                    count++;
                    
                    root->c[count]->accumulatedScore += DeleteLine(root->c[count]->recField);
                    
                }
            }
        }
        for(int i=count; i<40; i++)
        {
            root->c[count] = NULL;
        }
        for(int i=0; i<count; i++)
        {
            maketree(root->c[i]);
        }
        return;
    }
}
