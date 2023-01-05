//
//  main.c
//  과제2_자료구조
//
//  Created by Jeon Charn on 2021/03/30.
//

#include <stdio.h>
#include <stdlib.h>

int** readfile(char* filename);
void bubble_sort(int** arr);
void transpose(int** arr);

int main()
{
    int** file1 = readfile("A.txt");
    int** file2 = readfile("B.txt");
    int n = file1[0][0];
    int m = file1[0][1];
    int** add_file = (int**)malloc(sizeof(int*));
    int data_count = 0;

    add_file[0] = (int*)malloc(sizeof(int)*3);
    add_file[0][0] = n;
    add_file[0][1] = m;

    for(int i=1; i<=file1[0][2]; i++)
    {
        data_count++;
        add_file = (int**)realloc(add_file, sizeof(int*)*(data_count+1));
        add_file[data_count] = (int*)malloc(sizeof(int)*3);
        add_file[data_count][0] = file1[i][0];
        add_file[data_count][1] = file1[i][1];
        add_file[data_count][2] = file1[i][2];
    }
        
    for(int i=1; i<=file2[0][2]; i++)
    {
        for(int j=1; j<=file1[0][2]; j++)
        {
            if((file2[i][0]==add_file[j][0])&&(file2[i][1]==add_file[j][1]))
            {
                add_file[j][2]+=file2[i][2];
                break;
            }
            else if(j==file1[0][2])
            {
                data_count++;
                add_file = (int**)realloc(add_file, sizeof(int*)*(data_count+1));
                add_file[data_count] = (int*)malloc(sizeof(int)*3);
                add_file[data_count][0] = file2[i][0];
                add_file[data_count][1] = file2[i][1];
                add_file[data_count][2] = file2[i][2];
            }
        }
    }
    
    add_file[0][2] = data_count;
    
    bubble_sort(add_file);

    printf("<addition result>\n");
    for(int i=0; i<=add_file[0][2]; i++)
    {
        printf("%d %d %d\n", add_file[i][0], add_file[i][1], add_file[i][2]);
    }
    printf("\n");
    
    transpose(add_file);
    bubble_sort(add_file);
    
    printf("<transpose result>\n");
    for(int i=0; i<=add_file[0][2]; i++)
    {
        printf("%d %d %d\n", add_file[i][0], add_file[i][1], add_file[i][2]);
    }
    free(file1);
    free(file2);
    free(add_file);
    
    return 0;
}

int** readfile(char* filename)
{
    int n, m;
    int** return_data = (int**)malloc(sizeof(int*));
    return_data[0] = (int*)malloc(sizeof(int)*3);
    FILE* data = fopen(filename, "r");
    int arr_num; // file[i][j]의 원소를 저장할 변수
    int sparse_length = 1;
    
    fscanf(data, "%d %d", &n, &m);
    return_data[0][0] = n;
    return_data[0][1] = m;
    
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            fscanf(data, "%d", &arr_num);
            if(arr_num!=0)
            {
                sparse_length++;
                return_data = (int**)realloc(return_data, sizeof(int*)*sparse_length);
                return_data[sparse_length-1] = (int*)malloc(sizeof(int)*3);
                return_data[sparse_length-1][0] = i;
                return_data[sparse_length-1][1] = j;
                return_data[sparse_length-1][2] = arr_num;
            }
        }
    }
    return_data[0][2] = sparse_length-1;
    
    return return_data;
}

void bubble_sort(int** arr)
{
    for(int i=0; i<arr[0][2]; i++)
    {
        for(int j=1; j<arr[0][2]-i; j++)
        {
            if(arr[j][0]>arr[j+1][0])
            {
                int* save = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = save;
            }
            else if((arr[j][0]==arr[j+1][0])&&(arr[j][1]>arr[j+1][1]))
            {
                int* save = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = save;
            }
        }
    }
}

void transpose(int** arr)
{
    for(int i=1; i<=arr[0][2]; i++)
    {
        int save=arr[i][0];
        arr[i][0] = arr[i][1];
        arr[i][1] = save;
    }
    
    return;
}
