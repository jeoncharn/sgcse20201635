#include <stdio.h>

int main()
{
	int x, y;
	int* px=&x;
	int* py=&y;
	
	printf("input x, y: ");
	scanf("%d", &x);
	scanf("%d", &y);

	printf("px value: %d, px address: %p\n", *px, px);
	printf("py value: %d, py address: %p\n", *py, py);
	
	if(x>0)
	{
		if(y>0)
		{
			printf("(%d,%d) int quadrant 1\n", x, y);
		}
		
		else
		{
			printf("(%d,%d) int quadrant 4\n", x, y);
		}
	}
	else
	{
		if(y>0)
		{
			printf("(%d,%d) int quadrant 2\n", x, y);
		}
		
		else
		{
			printf("(%d,%d) int quadrant 3\n", x, y);
		}
	}
	
	return 0;
}
