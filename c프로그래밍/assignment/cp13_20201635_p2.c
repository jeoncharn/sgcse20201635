#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* new_strncpy(char** to_string, const char* from_string, int size);

int main()
{
	char* p = NULL;
	char* freeadd;
	char input[31];
	char buffer;
	int size;

	printf("input string: ");
	scanf("%30[^\n]", input);
	printf("input size = ");
	scanf("%d", &size);

	printf("before p = %s\n", p);
	freeadd=new_strncpy(&p, input, size);
	printf("after p = %s\n", p);

	free(freeadd);

	return 0;
}

char* new_strncpy(char** to_string, const char* from_string, int size)
{
	int maxlen;
	maxlen = strlen(from_string);

	if((*to_string)==NULL)
	{
		(*to_string) = (char*)malloc(sizeof(char)*(maxlen+1));
	}

	else
	{
		(*to_string) = (char*)realloc((*to_string), sizeof(char)*(maxlen+1));
	}

	if(size>=maxlen)
	{
		size = maxlen;
		strncpy(*to_string, from_string, size);
	}

	else if(size == 0)
	{
		size = maxlen;
		strncpy(*to_string, from_string, size);
	}

	else
	{
		strncpy(*to_string, from_string, size);
		(*to_string)[size] = '\0';
	}

	return (*to_string);
}
