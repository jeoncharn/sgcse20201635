//
//  count_func.c
//  star_wars
//
//  Created by Jeon Charn on 2021/03/16.
//

#include "header.h"

void count_func(long long int* count_arr, int num)
{
    for(int i=0; i<10; i++)
    {
        count_arr[i] = 0;
    }
    
    for(int i=1; i<=num; i++)
    {
        int number = i;
        while(number>=10)
        {
            count_arr[(number%10)] += 1;
            number = number/10;
        }
        count_arr[(number%10)] += 1;
        
    }
    
    return;
}
