#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* arr = malloc(sizeof(char));
	char scan;
	int i=0;
	int j=0;

	while(1)
	{
		scanf("%c", &scan);

		if(scan=='\n')
		{
			break;
		}
		
		arr[i]=scan;
		arr = (char*)realloc(arr, (i+2)*sizeof(char));
		i++;
	}

	while(1)
	{
		if(j==i)
		{
			printf("Yes\n");
			break;
		}

		if(arr[j]!=arr[i-1-j])
		{
			printf("No\n");
			break;
		}
		
		j++;
	}

	return 0;
}
