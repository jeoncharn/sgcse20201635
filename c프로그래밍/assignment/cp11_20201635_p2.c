#include <stdio.h>
#include <stdlib.h>

char* Encryption(char* Plaintext, int key);

int main()
{
	char str[31];
	char* ptr;
	int key;
	
	printf("Input the Plaintext: ");
	scanf("%[^\n]", str);
	printf("Input key: ");
	scanf("%d", &key);

	ptr=Encryption(str, key);
	printf("Encrypt(%s) = %s\n", str, ptr);
	printf("Decrypt(%s) = %s\n", ptr, Encryption(ptr,26-key));

	return 0;
}

char* Encryption(char* Plaintext, int key)
{
	char* out = (char*)malloc(31*sizeof(char));

	for(int i=0; Plaintext[i]!='\0'; i++)
	{
		if(Plaintext[i]>=65&&Plaintext[i]<=90)
		{
			if(Plaintext[i]+key>90)
			{
				out[i] = Plaintext[i]-26+key;
			}
			
			else
			{
				out[i] = Plaintext[i]+key;
			}
		}
		
		else if(Plaintext[i]>=97&&Plaintext[i]<=122)
		{
			if(Plaintext[i]+key>122)
			{
				out[i] = Plaintext[i]-26+key;
			}
			
			else
			{
				out[i] = Plaintext[i]+key;
			}
		}

		else
		{
			out[i] = Plaintext[i];
		}

		out[i+1] = '\0';
	}

	return out;
}

