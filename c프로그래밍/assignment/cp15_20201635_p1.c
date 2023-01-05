#include <stdio.h>
#include <string.h>

enum Date {sun = 0, mon, tue, wed, thu, fri, sat};

struct Calendar{
	int year, month, day;
	enum Date date;
	char* dateString;
};

enum Date getDate(int y, int m, int d);
char* getDay(enum Date currDate);

int main()
{
	struct Calendar info;

	scanf("%d", &info.year);
	scanf("%d", &info.month);
	scanf("%d", &info.day);
	
	info.date = getDate(info. year, info.month, info.day);

	strcpy(info.dateString, getDay(info.date));

	printf("%s\n", info.dateString);

	return 0;
}

enum Date getDate(int y, int m, int d)
{
	 return (y + y/4 - y/100 + y/400 + (13 * m + 8) / 5 + d) % 7;
}

char* getDay(enum Date currDate)
{
	if(currDate == 0)
	{
		return "Sunday";
	}

	else if(currDate == 1)
	{
		return "Monday";
	}

	else if(currDate == 2)
	{
		return "Tuesday";
	}

	else if(currDate == 3)
	{
		return "Wednesday";
	}

	else if(currDate == 4)
	{
		return "Thursday";
	}

	else if(currDate == 5)
	{
		return "Friday";
	}

	else if(currDate == 6)
	{
		return "saturday";
	}
}

