#include <stdio.h>

int itoa(int n, char s[]);

main()
{
	char s[1000];

	itoa(0, s);
	printf("%s\n", s);
	itoa(100, s);
	printf("%s\n", s);
	itoa(-21878, s);
	printf("%s\n", s);

	return 0;
}

/* itoa:  convert n to charcters in s, return number of
	characters written */
int itoa(int n, char s[])
{
	int i, sign;

	i = 0;
	if ((sign = n) < 0) {
		s[i++] = '-';
		n = -n;
	}
	if (n / 10 > 0)
		i += itoa(n / 10, s + i);
	s[i++] = n % 10 + '0';
	s[i] = '\0';

	return i;
}
