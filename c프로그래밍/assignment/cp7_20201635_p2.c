#include <stdio.h>

float cal_average(int a[][5], int n);
float cal_ratio(int a[][5], int n, float average);

int main()
{
	int score[10][5];
	int num;

	scanf("%d", &num);

	for(int i=0; i<num; i++)
	{
		for(int j=0; j<5; j++)
		{
			scanf("%d", &score[i][j]);
		}
	}

	printf("\n<score>\n");
	for(int i=0; i<num; i++)
	{
		for(int j=0; j<5; j++)
		{
			printf("%d ", score[i][j]);
		}
		printf("\n");
	}

	printf("\n<total_average>\n");
	printf("%.3f\n", cal_average(score, num));

	printf("\n<ratio>\n");
	printf("%.3f%%\n", cal_ratio(score, num, cal_average(score, num)));

	return 0;
}


float cal_average(int a[][5], int n)
{
	float sum=0;

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<5; j++)
		{
			sum+=a[i][j];
		}
	}

	return sum/(5*n);
}

float cal_ratio(int a[][5], int n, float average)
{
	float sum=0;
	float people=0;

	for(int i=0; i<n; i++)
	{
		for(int j=0; j<5; j++)
		{
			sum+=a[i][j];
		}
		
		if(sum/5>average)
		{
			people++;
		}

		sum=0;
	}

	return(people/n)*100;
}

