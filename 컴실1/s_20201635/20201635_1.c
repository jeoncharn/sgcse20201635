/* made by 20201635 jeoncharn */

#include <stdio.h>

int main()
{
	char star = '*';
	int count;

	scanf("%d", &count);

	for(int i=1; i<=count; i++)
	{
		for(int j=1; j<=i; j++)
		{
			printf("%c", star);
		}
		printf("\n");
	}

	return 0;
}

