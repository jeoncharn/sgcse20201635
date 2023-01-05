#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* chArr = (char*)calloc(1,sizeof(char));
	char scan;
	int i=0;
	
	printf("Input string:");
	while(1)
	{
		scanf("%c", &scan);

		if(scan==10)
		{
			break;
		}

		chArr[i]=scan;
		chArr = realloc(chArr, (i+2)*sizeof(char));
		i++;
	}

	printf("Output string:");
	while(1)
	{
		if(i<0)
		{
			break;
		}

		printf("%c", chArr[i]);

		i--;
	}

	printf("\n");

	return 0;
}

