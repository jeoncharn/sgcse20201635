/* made by 20201635 jeoncharn */

#include <stdio.h>
#include <stdlib.h>

int check(int** data, int width, int height);
void delete(int** data, int i, int j);

int main()
{
	int** data;
	int* count = (int*)malloc(sizeof(int));
	int number = 0;
	int width, height;

	while(1)
	{
		scanf("%d %d", &width, &height);
		if(width==0&&height==0)
		{
			break;
		}

		number++;
		count = (int*)realloc(count, sizeof(int)*number);

		
		data = (int**)malloc(sizeof(int*)*(height+2));
		for(int i=0; i<height+2; i++)
		{
			data[i] = (int*)malloc(sizeof(int)*(width+2));
		}

		for(int i=0; i<height+2; i++)
		{
			data[i][0] = 0;
			data[i][width + 1] = 0;
		}

		for(int i=0; i<width+2; i++)
		{
			data[0][i] = 0;
			data[height+1][i] = 0;
		}	

		for(int i=1; i<=height; i++)
		{
			for(int j=1; j<=width; j++)
			{
				scanf("%d", &data[i][j]);
			}
		}

		count[number-1] = check(data, width, height);

		for(int i=0; i<height+2; i++)
		{
			free(data[i]);
		}
		free(data);
	}

	for(int i=0; i<number; i++)
	{
		printf("%d\n", count[i]);
	}

	free(count);

	return 0;
}



int check(int** data, int width, int height)
{	
	int count = 0;
	for(int i=1; i<=height; i++)
	{
		for(int j=1; j<=width; j++)
		{
			if(data[i][j]==1)
			{
				count++;
				delete(data, i, j);
			}
		}
	}
	return count;
}

void delete(int** data, int i, int j)
{
	data[i][j] = 0;
	
	if(data[i-1][j-1]==1)
	{
		delete(data, i-1, j-1);
	}

	if(data[i-1][j]==1)
	{
		delete(data, i-1, j);
	}

	if(data[i-1][j+1]==1)
	{
		delete(data, i-1, j+1);
	}

	if(data[i][j-1]==1)
	{
		delete(data, i, j-1);
	}

	if(data[i][j+1]==1)
	{
		delete(data, i, j+1);
	}

	if(data[i+1][j-1]==1)
	{
		delete(data, i+1, j-1);
	}
	if(data[i+1][j]==1)
	{
		delete(data, i+1, j);
	}

	if(data[i+1][j+1]==1)
	{
		delete(data, i+1, j+1);
	}

	return;
}



