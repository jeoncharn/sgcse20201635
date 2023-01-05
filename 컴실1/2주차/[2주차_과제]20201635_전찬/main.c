//
//  main.c
//  star_wars
//
//  Created by Jeon Charn on 2021/03/16.
//

#include "header.h"

int main()
{
    int T;
    scanf("%d", &T);
    if(T<=0)
    {
        printf("input wrong value! input must be positive integer\n");
        return 0;
    }
    
    int* num_array = (int*)malloc(sizeof(int)*T);
    long long int** count_array = (long long int**)malloc(sizeof(long long int*)*T);
    for(int i=0; i<T; i++)
    {
        scanf("%d", &(num_array[i]));
        count_array[i] = (long long int*)malloc(sizeof(long long int)*10);
        count_func(count_array[i], num_array[i]);
    }
    
    print_func(count_array, T);
    
    return 0;
}
