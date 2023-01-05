#include <stdio.h>

char* getScientificFormatString(char* strPtr);

int main()
{
	char str[16];

	printf("Input scientific format number:\n");

	if(getScientificFormatString(str) == NULL)
	{
		printf("<result>\n");
		printf("|%-20s|\n", str);
	}
	else
	{
		printf("<result>\n");
		printf("|%20s|\n", str);
	}

	return 0;
}

char* getScientificFormatString(char* strPtr)
{
	scanf("%15[^\n]", strPtr);
	
	for(int i=0; strPtr[i]!='\0'; i++)
	{
		if(strPtr[i] == 'E'|| strPtr[i] == 'e')
		{
			for(int j=i+1; strPtr[j]!='\0'; j++)
			{
				if(strPtr[j] == '+'|| strPtr[j] == '-')
				{
					for(int k=j+1; strPtr[k+1]!='\0'; k++)
					{
						if(('0'<=strPtr[k]<='9')&&('0'<=strPtr[k+1]<='9'))
						{
							return strPtr;
						}
					}
				}
			}
		}
	}

	return NULL;
}
