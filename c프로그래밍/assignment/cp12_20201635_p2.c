#include <stdio.h>

void printByWord(char* str);

int main()
{
	char str[41];

	printf("Input string:\n");
	printByWord(str);

	return 0;
}

void printByWord(char* str)
{
	scanf("%40[^\n]", str);

	printf("<result>\n");

	if(((str[0]>='A')&&(str[0]<='Z'))||((str[0]>='a')&&(str[0]<='z')))
	{
		for(int i=0; str[i]!='\0'; i++)
		{
			if(str[i] == ' ')
			{
				printf("\n");
			}
			
			else
			{
				printf("%c", str[i]);
			}
		}
		printf("\n");
	}
	
	else
	{
		printf("%40.20s\n", str);
	}

	return;
}
