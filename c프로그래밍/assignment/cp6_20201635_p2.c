#include <stdio.h>

int mat_nul(int left[100][100], int right[100][100], int result[100][100], int N);

int main()
{
	int arr1[100][100], arr2[100][100], result[100][100];
	int n;

	printf("<Input number>\n");
	scanf("%d", &n);

	printf("<left>\n");
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			scanf("%d", &*(*(arr1+i)+j));
		}
	}

	printf("<right>\n");
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			scanf("%d", &*(*(arr2+i)+j));
		}
	}

	mat_nul(arr1, arr2, result, n);

	return 0;
}
	
int mat_nul(int left[100][100], int right[100][100], int result[100][100], int N)
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			for(int k=0; k<N; k++)
			{
				*(*(result+i)+j)+=(*(*(left+i)+k))*(*(*(right+k)+j));
			}
		}
	}

	printf("<result>\n");

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			printf("%d ", *(*(result+i)+j));
		}
		printf("\n");
	}

	return 0;
}

