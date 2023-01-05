//
//  print_func.c
//  star_wars
//
//  Created by Jeon Charn on 2021/03/16.
//

#include "header.h"

void print_func(long long int** count_matrix, int T)
{
    for(int i=0; i<T; i++)
    {
        for(int j=0; j<10; j++)
        {
            printf("%lli  ", count_matrix[i][j]);
        }
        printf("\n");
    }
    
    return;
}
