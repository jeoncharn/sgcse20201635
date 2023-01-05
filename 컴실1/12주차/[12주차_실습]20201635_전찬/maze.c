//
//  main.c
//  maze_problem
//
//  Created by Jeon Charn on 2021/05/31.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    //wall이 존재할 경우 1, 존재하지 않은 경우에 0을 값으로 갖는 변수이다.
    int rightwall;
    int downwall;
    int value; // 현재 블록이 속한 집합을 나타낸다.
} Mazeblock;

void makemaze(Mazeblock** array, int width, int height);
void savemaze(Mazeblock** array, int width, int height);

int set_value = 1; // 서로 다른 집합임을 보여주기 위해 사용하는 변수

int main() {
    int maze_width, maze_height;
    Mazeblock** maze_block;
    printf("Input the maze width: ");
    scanf("%d", &maze_width);
    printf("Input the maze height: ");
    scanf("%d", &maze_height);
    
    // block matrix 초기화
    maze_block = (Mazeblock**)malloc(sizeof(Mazeblock*)*maze_height);
    for(int i=0; i<maze_height; i++)
    {
        maze_block[i] = (Mazeblock*)malloc(sizeof(Mazeblock)*maze_width);
        for(int j=0; j<maze_width; j++)
        {
            maze_block[i][j].x = j;
            maze_block[i][j].y = i;
            maze_block[i][j].rightwall = 1;
            maze_block[i][j].downwall = 1;
            maze_block[i][j].value = 0;
        }
    }
    
    makemaze(maze_block, maze_width, maze_height);
    savemaze(maze_block, maze_width, maze_height);
    
    return 0;
}

void makemaze(Mazeblock** array, int width, int height)
{
    //maze의 첫번째 줄 초기화
    for(int i=0; i<width; i++)
    {
        array[0][i].value = set_value;
        set_value++;
    }
    
    //2~4를 반복
    for(int i=0; i<height-1; i++)
    {
        //2의 과정 (합치거나 합치지 않으며, 합치는 경우 벽을 삭제해준다.)
        //현재 각각이 다 막혀있는 상태,
        for(int j=0; j<width-1; j++)
        {
            if(array[i][j].value!=array[i][j+1].value)
            {
                //rand()%2 를 통해서 0 또는 1의 값을 return 해준다
                if(rand()%2)
                {
                    array[i][j].rightwall = 0;
                    int value_save = array[i][j+1].value;
                    //집합에 포함되는 나머지 block도 같은 집합에 포함시킨다
                    for(int k=0; k<width; k++)
                    {
                        if(array[i][k].value==value_save)
                        {
                            array[i][k].value = array[i][j].value;
                        }
                    }
                }
            }
        }
        
        //3의 과정 (아래로 내리며, 각 집합에서 최소 1개는 내린다.)
        int test = 0;
        while(test==0)
        {
            test = 0;
            for(int j=0; j<width; j++)
            {
                array[i][j].downwall = rand()%2;
            }
            
            for(int j=0; j<width; j++)
            {
                if(array[i][j].downwall==1) // 벽이 막혀있는 경우
                {
                    for(int k=0; k<width; k++)
                    {
                        if(array[i][k].value==array[i][j].value&&array[i][k].downwall==0)
                        {
                            test = 1;
                            break;
                        }
                        else // 찾지 못한 경우에
                        {
                            test = 0;
                        }
                    }
                    if(test==0)
                    {
                        break;
                    }
                }
                
            }
        }
        
        for(int j=0; j<width; j++)
        {
            if(array[i][j].downwall==0)
            {
                array[i+1][j].value = array[i][j].value;
            }
        }
        
        
        //4의 과정 (value=0인 block을 새로운 집합으로 만들어주기)
        for(int j=0; j<width; j++)
        {
            if(array[i+1][j].value==0)
            {
                array[i+1][j].value = set_value;
                set_value++;
            }
        }
    }
    
    //마지막 처리 과정 (맞닿은 두 집합이 다르면)
    for(int i=0; i<width-1; i++)
    {
        if(array[height-1][i].value!=array[height-1][i+1].value)
        {
            array[height-1][i].rightwall = 0;
            int value_save = array[height-1][i+1].value;
            for(int j=0; j<width; j++)
            {
                if(array[height-1][j].value==value_save)
                {
                    array[height-1][j].value = array[height-1][i].value;
                }
            }
        }
    }
    
    return;
}

void savemaze(Mazeblock** array, int width, int height)
{
    FILE* mazefile = fopen("maze.maz", "w");
    //file의 첫번째 줄 저장하기
    for(int i=0; i<width; i++)
    {
        fprintf(mazefile, "+-");
    }
    fprintf(mazefile, "+\n");
    
    for(int i=0; i<height; i++)
    {
        fprintf(mazefile, "|");
        for(int j=0; j<width; j++)
        {
            if(array[i][j].rightwall==1)
            {
                fprintf(mazefile, " |");
            }
            else
            {
                fprintf(mazefile, "  ");
            }
        }
        fprintf(mazefile, "\n");
        fprintf(mazefile, "+");
        for(int j=0; j<width; j++)
        {
            if(array[i][j].downwall==1)
            {
                fprintf(mazefile, "-+");
            }
            else
            {
                fprintf(mazefile, " +");
            }
        }
        fprintf(mazefile, "\n");
    }
    
    fclose(mazefile);
    
    return;
}
