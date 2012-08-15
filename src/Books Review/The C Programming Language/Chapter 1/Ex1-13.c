/* a horizontal histrogram */
#include <stdio.h>
#define MAXWORDLEN 10
int main()
{
	char c;
	int i, j;
	int inword = 0;
	int nlength[MAXWORDLEN + 1];
	int nword = 0;

	for(i = 0; i <= MAXWORDLEN; i++)
	{
		nlength[i] = 0;
	}

	while((c = getchar()) != EOF)
	{
		if(c == ' ')
		{
			if(inword == 1)
			{
				if(nword < 10)
					nlength[nword]++;
				else
					nlength[MAXWORDLEN]++;
			}
				
			inword = 0;
			nword = 0;
		}
		else
		{
			nword++;
			inword = 1;
		}
	}
	for(i = 1; i <= MAXWORDLEN; i++)
	{
		printf("| %d| ", i);
		for(j = 0; j < nlength[i]; j++)
			printf("*");
		printf("\n");
	}

	return 0;
}