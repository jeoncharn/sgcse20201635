#include <stdio.h>

struct money
{
	int coin1, coin2, coin3, coin4;
};

int main()
{
	int num, rest;
	struct money info;

	printf("Change: ");
	scanf("%d", &num);

	info.coin1 = num / 500;
	num = num % 500;

	info.coin2 = num / 100;
	num = num % 100;
	
	info.coin3 = num / 50;
	num = num % 50;

	info.coin4 = num / 10;
	num = num % 10;

	printf("500 : %d\n100 : %d\n50 : %d\n10 : %d\n", info.coin1, info.coin2, info.coin3, info.coin4);

	return 0;
}

