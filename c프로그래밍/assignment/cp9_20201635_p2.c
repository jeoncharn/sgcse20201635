#include <stdio.h>
#include <stdlib.h>

void double_double(int** a, int* size);

int main()
{
	int N;
	int* Arr;
	
	scanf("%d", &N);

	Arr = (int*)malloc(N*sizeof(int));
	for(int i=0; i<N; i++)
	{
		scanf("%d", &Arr[i]);
	}


	double_double(&Arr, &N);

	for(int i=0; i<N; i++)
	{
		printf("%d ", Arr[i]);
	}

	printf("\n");

	return 0;
}

void double_double(int** a, int* size)
{
	*a = realloc(*a, (*size)*2*sizeof(int));
	
	for(int i=0; i<(*size); i++)
	{
		(*a)[i+(*size)] = ((*a)[i])*2;
	}

	*size=(*size)*2;

	for(int i=0; i<*size; i++)
	{
		for(int j=0; j<*size-i-1; j++)
		{
			if((*a)[j]>(*a)[j+1])
			{
				int k=(*a)[j];
				(*a)[j]=(*a)[j+1];
				(*a)[j+1]=k;
			}
		}
	}

	return;
}
