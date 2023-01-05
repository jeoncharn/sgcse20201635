#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int numerator;
	int denominator;
}FRACTION;

void multFr(FRACTION* pFr1, FRACTION* pFr2, FRACTION* pRes);

int main()
{
	FRACTION fr1, fr2, res;

	printf("x/y : ");
	scanf("%d/%d", &(fr1.numerator), &(fr1.denominator));

	printf("x/y : ");
	scanf("%d/%d", &(fr2.numerator), &(fr2.denominator));

	printf("\n");

	multFr(&fr1, &fr2, &res);

	printf("%d/%d", fr1.numerator, fr1.denominator);
	printf(" * ");
	printf("%d/%d", fr2.numerator, fr2.denominator);
	printf(" = ");
	printf("%d/%d\n", res.numerator, res.denominator);

	return 0;
}

void multFr(FRACTION* pFr1, FRACTION* pFr2, FRACTION* pRes)
{
	pRes->numerator = (pFr1->numerator) * (pFr2->numerator);
	pRes->denominator = (pFr1->denominator) * (pFr2->denominator);

	return;
}

