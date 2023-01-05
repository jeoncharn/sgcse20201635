//
//  main.c
//  과제1_자료구조
//
//  Created by Jeon Charn on 2021/03/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int* array, int length);

int main(int argc, char* argv[])
{
    FILE* data = fopen(argv[1], "r");
    int line_num;
    int count = 0;
    int* arr = (int*)malloc(sizeof(int)*1);
    while(1)
    {
        if((fscanf(data, "%d", &line_num)) == EOF)
        {
            break;
        }
        else
        {
            arr[count] = line_num;
            count++;
            arr = (int*)realloc(arr, sizeof(int)*(count+1)); //realloc 1일때 문제가 생길수도 있을듯
        }
    }
    printf("Input\t: ");
    for(int i=0; i<count; i++)
    {
        printf("%d ", arr[i]);
    }
    
    insertion_sort(arr, count);
    
    printf("\nSorted\t: ");
    for(int i=0; i<count; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
    
    free(arr);
    fclose(data);
    
    printf("    n\trepititions\ttime\n");
    for(int n=0; n<=100; n=n+10)
    {
        double time_sum = 0;
        int rep = n+1; // n=0일때도 반비례를 만들어주기 위해서 1을 더함
        int* time_arr = (int*)malloc(sizeof(int)*n);
        for(int i=1; i<=500/rep; i++)
        {
            for(int j=0; j<n; j++)
            {
                time_arr[j] = n-i;
            }
            clock_t start = clock();
            insertion_sort(time_arr, n);
            time_sum += ((double)(clock()-start)/CLOCKS_PER_SEC);
        }
        printf("    %d\t%11d\t%lf\n", n, 500/rep, (time_sum/(double)(500/rep)));
        free(time_arr);
    }
    return 0;
}

void insertion_sort(int* array, int length)
{
    for(int i=1; i<length; i++)
    {
        for(int j=0; j<i; j++)
        {
            if(array[i]<array[j])
            {
                int save_num = array[i];
                for(int k=i; k>=j+1; k--)
                {
                    array[k] = array[k-1];
                }
                array[j] = save_num;
                break;
            }
        }
    }
    
    return;
}
