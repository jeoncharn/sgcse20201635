#include <stdio.h>

void addition(int* num1, int num2);

int main()
{
	int a;
	int b=5;
	printf("Input a number: ");
	scanf("%d", &a);

	addition(&a, b);
	
	printf("addition(%d, %d)=%d\n", a-b, b, a);

	return 0;
}

void addition(int* num1, int num2)
{
	*num1+=num2;

	return;
}

