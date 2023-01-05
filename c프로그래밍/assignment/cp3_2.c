#include <stdio.h>

void convertTime(int hours, int minutes, int seconds, int* timeInSeconds);

int main()
{
	int timeInSeconds, hours, minutes, seconds;
	
	printf("Input a number (hours, minutes, seconds): ");
	scanf("%d %d %d", &hours, &minutes, &seconds);

	convertTime(hours, minutes, seconds, &timeInSeconds);

	printf("Convert hours: %d, minutes: %d, seconds: %d to\n timeInSeconds: %d\n", hours, minutes, seconds, timeInSeconds);

	return 0;
}

void convertTime(int hours, int minutes, int seconds, int* timeInSeconds)
{
	*timeInSeconds=3600*hours;
	*timeInSeconds+=60*minutes;
	*timeInSeconds+=seconds;

	return;
}

