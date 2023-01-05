#include <stdio.h>
#include <string.h>

void splitString(char* str, char* word1, char* word2);

int main()
{
	char str[31];
	char word1[16];
	char word2[16];
	
	printf("Input str:\n");
	scanf("%[^\n]", str);
	
	splitString(str, word1, word2);

	printf("<result>\n");
	printf("[%s] -> [%s][%s]\n", str, word1, word2);

	return 0;
}

void splitString(char* str, char* word1, char* word2)
{
	int len = strlen(str);

	if(len%2==0)
	{
		strncpy(word1, str, len/2);
		strncpy(word2, str + (len/2), len/2);
	}

	else
	{
		strncpy(word1, str, len/2);
		strncpy(word2, str + (len/2), (len/2)+1);
	}

	return;
}

