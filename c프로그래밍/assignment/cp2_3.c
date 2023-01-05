#include <stdio.h>

void swap(int* a, int* b);
void bubble(int* a, int* b, int* c);

int main()
{
	int num1, num2, num3;

	printf("Input 3 numbers: ");
	scanf("%d %d %d", &num1, &num2, &num3);

	bubble(&num1, &num2, &num3);

	printf("After sorting: %d %d %d\n", num1, num2, num3);
	
	return 0;
}

void swap(int* a, int* b)
{
	if(*a>*b)
	{
		int c=*a;
		*a=*b;
		*b=c;
	}

	return;
}

void bubble(int* a, int* b, int* c)
{
	swap(b, c);
	swap(a, b);
	swap(a, c);
	swap(b, c);
	
	return;
}
