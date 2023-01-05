#include <stdio.h>

int main()
{
	int arr[100][100];
	int i=1;
	int n;
	
	printf("<Input number>\n");
	scanf("%d", &n);

	for(int p=0; p<n; p++)
	{
		for(int q=0; q<n; q++)
		{
			*(*(arr+p)+q)=i;
			i++;
		}
	}

	for(int p=0; p<n; p++)
	{
		for(int q=0; q<n; q++)
		{
			printf("%-3d", *(*(arr+p)+q));
		}
		printf("\n");
	}

	return 0;
}

