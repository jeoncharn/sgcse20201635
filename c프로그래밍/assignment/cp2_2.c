#include <stdio.h>

void swap(char** a, char** b);

int main()
{
	char* str1="she can do, he can do";
	char* str2="why not me?";

	printf("Before swapping\n\n");

	printf("str1=%s, address: %p\n",str1, str1);
	printf("str2=%s, address: %p\n\n", str2, str2);

	swap(&str1, &str2);

	printf("After swapping\n\n");

	printf("str1=%s, address: %p\n", str1, str1);
	printf("str2=%s, address: %p\n", str2, str2);

	return 0;
}

void swap(char** a, char** b)
{
	char* c=*a;
	*a=*b;
	*b=c;
	
	return;
}
