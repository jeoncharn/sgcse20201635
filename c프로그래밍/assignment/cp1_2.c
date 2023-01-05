#include <stdio.h>

int main()
{
	int a, b;
	int* p=&a;
	int*  q=&b;
	int* p2=p;
	int* q2=q;

	printf("Input a, b: ");
	scanf("%d %d", &a, &b);
	
	printf("p value: %d, p address: %p\n", *p, p);
	printf("q value: %d, q address: %p\n\n", *q, q);

	printf("p2 value: %d, p2 address: %p\n", *p2, p2);
	printf("q2 value: %d, q2 address: %p\n", *q2, q2);

	return 0;
}

