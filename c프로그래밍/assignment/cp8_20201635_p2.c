#include <stdio.h>
#include <stdlib.h>

int* get_next_process(int* prev_pointer, int size);

int main()
{
	int N;
	int* prev;
	
	scanf("%d", &N);
	prev = (int*)malloc(sizeof(int)*N);
	for(int i=0; i<N; i++)
	{
		scanf("%d", &prev[i]);
	}

	for(int i=0; i<N/2; i++)
	{
		int a=prev[i];
		prev[i]=prev[N-i-1];
		prev[N-i-1]=a;
	} // 이거 맞나?

	while(N!=1)
	{
		prev = get_next_process(prev, N);

		if(N%2==0)
		{
			N=N/2;
		}

		else
		{
			N=N/2+1;
		}

		for(int i=0; i<N; i++)
		{
			printf("%d ", prev[i]);
		}

		printf("\n");

	}

	return 0;
}

int* get_next_process(int* prev_pointer, int size)
{
	int next_size;
	int* next_pointer;

	if(size%2==0)
	{
		next_size=size/2;
	}
	else
	{
		next_size=size/2+1;
	}

	next_pointer = (int*)malloc(sizeof(int)*next_size);

	for(int i=0; i<next_size-1; i++)
	{
		next_pointer[i]=prev_pointer[2*i]+prev_pointer[2*i+1];
	}

	if(size%2==0)
	{
		next_pointer[next_size-1]=prev_pointer[size-2]+prev_pointer[size-1];
	}
	else
	{
		next_pointer[next_size-1]=prev_pointer[size-1];
	}

	return next_pointer;
}

