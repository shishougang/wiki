/* a vertical histrogram */
#include <stdio.h>
#define MAXWORDLEN 10
int main()
{
	char c;
	int i, j;
	int inword = 0;
	int nlength[MAXWORDLEN + 1];
	int nword = 0;
	int Maxlength;
	Maxlength = 0;

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
				{
					nlength[nword]++;
					Maxlength = nlength[nword] > Maxlength? nlength[nword] : Maxlength;
				}
				else
				{
					nlength[MAXWORDLEN]++;
					Maxlength = nlength[MAXWORDLEN] > Maxlength? nlength[MAXWORDLEN] : Maxlength;
				}

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
	for(i = Maxlength; i >= 1; i--)
	{
		printf("%4d | ");
		
	}

	return 0;
}