#include <stdio.h>

void find(int* arr, int n);

int main()
{
	int arr[100];
	int length;
	
	scanf("%d", &length);
	
	for(int i=0; i<length; i++)
	{
		scanf("%d", &arr[i]);
	}

	find(arr, length);

	return 0;
}

void find(int* arr, int n)
{
	int count=0;

	for(int j=0; j<10; j++)
	{
		for(int i=0; i<n; i++)
		{
			if(arr[i]==j)
			{
				count++;
			}
		}
		printf("%d\n", count);
		count=0;
	}

	return;
}

