#include <stdio.h>

void swap(int* a, int* b);
void sort(int* a, int n);
void print_array(int* a, int n);

int main()
{
	int arr[1000];
	int length;
	int i=0;

	printf("Length of array: ");
	scanf("%d", &length);
	printf("\n");
	printf("Before: ");
	
	while(i<length)
	{
		scanf("%d", (arr+i));
		i++;
	}

	printf("\n");
	
	sort(arr, length);
	print_array(arr, length);

	return 0;
}

void swap(int* a, int* b)
{
	int c=*a;
	*a=*b;
	*b=c;

	return;
}

void sort(int* a, int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n-i-1; j++)
		{
			if(*(a+j)>*(a+j+1))
			{
				swap(a+j, a+j+1);
			}
		}
	}

	return;


}

void print_array(int* a, int n)
{
	printf("AfterSort: ");

	for(int i=0; i<n; i++)
	{
		printf("%d ", *(a+i));
	}

	printf("\n");

	return;
}

