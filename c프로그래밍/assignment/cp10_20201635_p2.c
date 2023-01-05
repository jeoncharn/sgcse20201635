#include <stdio.h>
#include <stdlib.h>

int** rotate(int** matrix, int n);
int** transpose(int** matrix, int n);
int** anti_clockwise(int** matrix, int n);


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

	matrix=anti_clockwise(matrix, N);

	printf("\n<anti_clockwise>\n");
	
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	matrix=anti_clockwise(matrix, N);
	matrix=anti_clockwise(matrix, N);
	matrix=anti_clockwise(matrix, N);

	matrix=transpose(matrix, N);

	printf("\n<transpose>\n");

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

int** anti_clockwise(int** matrix, int n)
{
	int** matrix2;
	matrix2 = (int**)malloc(sizeof(int*)*n);
	for(int i=0; i<n; i++)
	{
		matrix2[i] = (int*)malloc(sizeof(int)*n);
	}
	
	for(int k=0; k<3; k++)
	{
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				matrix2[i][j] = matrix[n-1-j][i];
				
			}
		}
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<n; j++)
			{
				matrix[i][j] = matrix2[i][j];
			}
		}
	}

	return matrix2;
}

int** transpose(int** matrix, int n)
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
			matrix2[i][j] = matrix[j][i];
		}
	}

	return matrix2;
}

