#include <stdio.h>

void printRange(char* str, int start, int end);

int main()
{
	char str[100]={""};
	int a, b;
	printf("Input string: ");
	scanf("%[^\n]s", str);
	printf("Input start and end: ");
	scanf("%d %d", &a, &b);

	printRange(str, a, b);

	return 0;
}

void printRange(char* str, int start, int end)
{
	for(int i=start; i<end; i++)
	{
		printf("%c", str[i]);
	}
	printf("\n");

	return;
}

