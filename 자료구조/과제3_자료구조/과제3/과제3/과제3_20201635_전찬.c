//
//  main.c
//  과제3
//
//  Created by Jeon Charn on 2021/04/06.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_size 100

int nfind(char* string, char* pat);
int ntime(char* string, char* pat);

int pmatch(char* string, char* pat, int* failure);
int kmptime(char* string, char* pat, int* failure);
void fail(char* pat, int* failure);

int main()
{
    char string_line[max_size];
    char pat_line[max_size];
    int failure[max_size];
    
    FILE* input = fopen("input.txt", "r");
    
    fgets(string_line, max_size, input);
    string_line[strlen(string_line)-1] = '\0'; //fgets에서 \n을 지우기 위한 작업
    fgets(pat_line, max_size, input);
    pat_line[strlen(pat_line)-1] = '\0';
    
    //O(n^2)을 이용한 pattern matching
    if(nfind(string_line, pat_line)==-1)
    {
        printf("NO ");
    }
    else
    {
        printf("YES ");
    }
    
    printf("%d\n", ntime(string_line, pat_line));
    
    
    //kmp를 이용한 pattern matching
    
    fail(pat_line, failure);
    
    if(pmatch(string_line, pat_line, failure)==-1)
    {
        printf("NO ");
    }
    else
    {
        printf("YES ");
    }
    
    printf("%d\n", kmptime(string_line, pat_line, failure));
    
    return 0;
}



int nfind(char* string, char* pat)
{
    int i,j = 0,start = 0;
    int lasts = (int)strlen(string)-1;
    int lastp = (int)strlen(pat)-1;
    int endmatch = lastp;
    for(i=0; endmatch<=lasts; endmatch++, start++)
    {
        if(string[endmatch] == pat[lastp])
        {
            for(j=0, i=start; j<lastp && string[i]==pat[j]; i++, j++)
            {
                
            }
        }
        if(j==lastp)
        {
            return start;
        }
    }
    return -1;
}

int ntime(char* string, char* pat)
{
    int i,j = 0,start = 0;
    int time = 0;
    int lasts = (int)strlen(string)-1;
    int lastp = (int)strlen(pat)-1;
    int endmatch = lastp;
    for(i=0; endmatch<=lasts; endmatch++, start++)
    {
        if(string[endmatch] == pat[lastp])
        {
            for(j=0, i=start; j<lastp && string[i]==pat[j]; i++, j++)
            {
                time++;
            }
        }
        else
        {
            time++;
        }
        
        if(j==lastp)
        {
            break;
        }
    }
    return time;
}
 
/*int ntime(char* string, char* pat)
{
    int time = 0;
    int lens = (int)strlen(string);
    int lenp = (int)strlen(pat);
    for(int i=0; i<lens-lenp; i++)
    {
        for(int j=0; j<lenp; j++)
        {
            time++;
            if(pat[j]!=string[i+j])
            {
                break;
            }
            else if(j==lenp-1)
            {
                return time;
            }
        }
    }
    
    return time;
}
*/

int pmatch(char* string, char* pat, int* failure)
{
    int i = 0;
    int j = 0;
    int lens = (int)strlen(string);
    int lenp = (int)strlen(pat);
    
    while(i<lens && j<lenp)
    {
        if(string[i] == pat[j])
        {
            i++;
            j++;
        }
        
        else if(j==0)
        {
            i++;
        }
        
        else
        {
            j = failure[j-1] + 1;
        }
        
    }
    
    return ((j==lenp) ? (i-lenp) : -1);
}


int kmptime(char* string, char* pat, int* failure) // pmatch를 return만 변형해서 제작
{
    int i = 0;
    int j = 0;
    int time = 0;
    int lens = (int)strlen(string);
    int lenp = (int)strlen(pat);
    
    while(i<lens && j<lenp)
    {
        if(string[i] == pat[j])
        {
            i++;
            j++;
        }
        
        else if(j==0)
        {
            i++;
        }
        
        else
        {
            j = failure[j-1] + 1; //-1을 해주어야 하나?
        }
        
        time ++;
        
    }
    
    return time;
}

/*
void fail(char* pat, int* failure)
{
    int i, n = (int)strlen(pat);
    failure[0] = -1;
    for(int j=1;j<n;j++)
    {
        i = failure[j-1];
        while ((pat[j] != pat[i+1]) && (i >= 0))
        {
            i = failure[i];
        }
        
        if (pat[j] == pat[i+1])
        {
            failure[j] = i+1;
        }
        
        else
        {
            failure[j] = -1;
        }
    }
}
*/
 
void fail(char* pat, int* failure)
{
    int size = (int)strlen(pat);
    failure[0] = -1;
    
    for(int j=1; j<size; j++)
    {
        if(failure[j-1]==-1)
        {
            if(pat[j]==pat[0])
            {
                failure[j] = 0;
            }
            else
            {
                failure[j] = -1;
            }
        }
        else
        {
            if(pat[j]==pat[failure[j-1] + 1])
            {
                failure[j] = failure[j-1] + 1;
            }
            
            else
            {
                if(pat[j]==pat[0])
                {
                    failure[j] = 0;
                }
                else
                {
                    failure[j] = -1;
                }
            }
        }
    }
}
