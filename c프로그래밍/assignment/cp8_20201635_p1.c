#include <stdio.h>
#include <stdlib.h>

char* triple_concatenate(char* str1, char* str2, char* str3);
int n1, n2, n3;

int main()
{
	char* str1;
	char* str2;
	char* str3;
	char* result;
	printf("Input size of str1: ");
	scanf("%d", &n1);
	getchar();
	str1 = (char*)malloc(sizeof(char)*n1);
	printf("Input str1: ");
	gets(str1);

	printf("Input size of str2: ");
	scanf("%d", &n2);
	getchar();
	str2 = (char*)malloc(sizeof(char)*n2);
	printf("Input str2: ");
	gets(str2);

	printf("Input size of str3: ");
	scanf("%d", &n3);
	getchar();
	str3 = (char*)malloc(sizeof(char)*n3);
	printf("Input str3: ");
	gets(str3);

	result = (char*)malloc(sizeof(char)*(n1+n2+n3));
	result = triple_concatenate(str1, str2, str3);
	printf("\n\nResult: %s\n", result);

	return 0;
}

char* triple_concatenate(char* str1, char* str2, char* str3)
{
	char* result;

	result = (char*)malloc(sizeof(char)*(n1+n2+n3));

	for(int i=0; i<n1; i++)
	{
		result[i] = str1[i];
	}

	for(int i=0; i<n2; i++)
	{
		result[n1+i] = str2[i];
	}

	for(int i=0; i<n3; i++)
	{
		result[n1+n2+i] = str3[i];
	}

	return result;
}


