#include <stdio.h>
int main(int argc, char const *argv[])
{
	
	int inwordflag = 1;
	while((c = getchar()) != EOF)
	{
		if(c == '\t' || c == ' ' || c == '\n')
		{
			if(inwordflag == 1)
			{
				putchar('\n');
				inwordflag = 0;
			}
				
		}
		else
		{
			inwordflag = 1;
			putchar(c);
		}
	}
	return 0;
}