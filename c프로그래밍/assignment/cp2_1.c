#include <stdio.h>

void findMax(int num1, int num2, int* maximum);

int main()
{
	int a, b, c;

	printf("Input number:");
	scanf("%d %d", &a ,&b);

	findMax(a, b, &c);

	printf("Result: %d\n", c);

	return 0;
}

void findMax(int num1, int num2, int* maximum)
{
	if(num1>num2)
	{
		*maximum=num1;
	}

	else
	{
		*maximum=num2;
	}
	
	return;
}
