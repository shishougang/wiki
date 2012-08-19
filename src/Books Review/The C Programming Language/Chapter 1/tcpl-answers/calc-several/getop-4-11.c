#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
	static int last = EOF;
	int i, c;

	if (last != EOF)
		s[0] = c = last;
	else
		s[0] = c = getch();
	while (c == ' ' || c == '\t')
		s[0] = c = getch();
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;	/* not a number */
	i = 0;
	if (isdigit(c))	/* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')	/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	last = c;
	return NUMBER;
}
