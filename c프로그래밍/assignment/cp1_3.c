#include <stdio.h>

int main()
{
	float num1, num2, num3;
	char oper;
	float* ref1=&num1;
	float* ref2=&num2;

	printf("Input operand 1: ");
	scanf("%f", &num1);
	printf("Input operand 2: ");
	scanf("%f", &num2);
	printf("\nInput operator: ");
	getchar();
	oper=getchar();

	printf("%c\n", oper);	

	if(oper==42)
	{
		num3=(*ref1)*(*ref2);
	}
	
	else if(oper==47)
	{
		num3=(*ref1)/(*ref2);
	}

	else if(oper==43)
	{
		num3=*ref1+*ref2;
	}
	
	else if(oper==45)
	{
		num3=*ref1-*ref2;
	}

	printf("\nResult: %f\n", num3);

	return 0;
}

