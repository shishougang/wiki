#include <ctype.h>
#include <stdio.h>

#define SIZE 3

main()
{
	int n, array[SIZE], getint(int *), getfloat(float *);
	float farray[SIZE];

	for (n = 0; n < SIZE; n++)
		array[n] = 0;
	for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
		;
	for (n = 0; n < SIZE; n++)
		printf("%d\n", array[n]);

	for (n = 0; n < SIZE; n++)
		farray[n] = 0;
	for (n = 0; n < SIZE && getfloat(&farray[n]) != EOF; n++)
		;
	for (n = 0; n < SIZE; n++)
		printf("%f\n", farray[n]);

	return 0;
}

int getch(void);
void ungetch(int);

/* getint:  get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch()))	/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);		/* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit(c)) {
			ungetch(c);	/* it's not a number */
			ungetch((sign < 0) ? '-' : '+');
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

/* getfloat:  get next float from input into *pn */
int getfloat(float *pn)
{
	int c;
	float sign, power;

	while (isspace(c = getch()))	/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);		/* it's not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit(c)) {
			ungetch(c);	/* it's not a number */
			ungetch((sign < 0) ? '-' : '+');
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10.0 * *pn + (c - '0');
	if (c == '.')
		c = getch();
	for (power = 1.0; isdigit(c); c = getch()) {
		*pn = 10.0 * *pn + (c - '0');
		power *= 10.0;
	}
	*pn = *pn * sign / power;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)	/* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
