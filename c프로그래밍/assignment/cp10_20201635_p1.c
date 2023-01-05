#include <stdio.h>
#include <stdlib.h>

int** rotate(int** matrix, int n);

int main()
{
	int N;
	int** matrix;

	scanf("%d", &N);
	matrix = (int**) malloc (sizeof(int*)*N);
	for(int i=0; i<N; i++)
	{
		matrix[i] = (int*) malloc (sizeof(int)*N);
	}
	
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			scanf("%d", &matrix[i][j]);
		}
	}

	matrix=rotate(matrix, N);

	printf("<result>\n");
	
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	return 0;
}

int** rotate(int** matrix, int n)
{
	int** matrix2;
	matrix2 = (int**)malloc(sizeof(int*)*n);
	for(int i=0; i<n; i++)
	{
		matrix2[i] = (int*)malloc(sizeof(int)*n);
	}
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			matrix2[i][j] = matrix[n-1-j][i];
		}
	}

	return matrix2;
}

