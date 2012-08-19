#include <limits.h>
#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);

void itob(int n, char s[], int b);

void itoapad(int n, char s[], int width);

void reverse(char s[]);

main()
{
	char s[1000];

	itoa(100, s);
	printf("%s\n", s);
	itob(100, s, 16);
	printf("%s\n", s);
	itoapad(100, s, 5);
	printf("%s\n", s);
	itoa(INT_MIN, s);
	printf("%s\n", s);
	itob(INT_MIN, s, 3);
	printf("%s\n", s);
	itoapad(INT_MIN, s, 4);
	printf("%s\n", s);

	return 0;
}

/* itoa:  convert n to characters in s */
void itoa(int n, char s[])
{
	int i, d, sign;

	sign = n;	/* record sign */
	i = 0;
	do {	/* generate digits in reverse order */
		d = n % 10;		/* get next digit */
		if (d < 0)
			d = -d;
		s[i++] = d + '0';
	} while ((n /= 10) != 0);	/* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void itob(int n, char s[], int b)
{
	const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i, d, sign;

	if (b < 0 || b > sizeof(digits) / sizeof(*digits))
		b = sizeof(digits) / sizeof(*digits);
	sign = n;
	i = 0;
	do {
		d = n % b;
		if (d < 0)
			d = -d;
		s[i++] = digits[d];
	} while ((n /= b) != 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void itoapad(int n, char s[], int width)
{
	int i, d, sign;

	sign = n;	/* record sign */
	i = 0;
	do {	/* generate digits in reverse order */
		d = n % 10;		/* get next digit */
		if (d < 0)
			d = -d;
		s[i++] = d + '0';
	} while ((n /= 10) != 0);	/* delete it */
	if (sign < 0)
		s[i++] = '-';
	width -= i;
	while (width-- > 0)
		s[i++] = ' ';
	s[i] = '\0';
	reverse(s);
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
