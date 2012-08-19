#include <stdio.h>

/* print a histogram of the frequencies of different characters
	in its input */
main()
{
	int c, i, max;
	int uppers['Z' - 'A'], lowers['z' - 'a'], digits['9' - '0'];

	for (i = 0; i <= 'Z' - 'A'; ++i)
		uppers[i] = 0;
	for (i = 0; i <= 'z' - 'a'; ++i)
		lowers[i] = 0;
	for (i = 0; i <= '9' - '0'; ++i)
		digits[i] = 0;

	while ((c = getchar()) != EOF) {
		if (c >= 'A' && c <= 'Z')
			++uppers[c - 'A'];
		else if (c >= 'a' && c <= 'z')
			++lowers[c - 'a'];
		else if (c >= '0' && c <= '9')
			++digits[c - '0'];
	}

	max = 0;
	for (i = 0; i <= 'Z' - 'A'; ++i) {
		if (uppers[i] > max)
			max = uppers[i];
	}
	for (i = 0; i <= 'z' - 'a'; ++i) {
		if (lowers[i] > max)
			max = lowers[i];
	}
	for (i = 0; i <= '9' - '0'; ++i) {
		if (digits[i] > max)
			max = digits[i];
	}
	for (; max >= 0; --max) {
		for (i = 0; i <= 'Z' - 'A'; ++i) {
			if (uppers[i] <= max)
				putchar(' ');
			else
				putchar('#');
		}
		for (i = 0; i <= 'z' - 'a'; ++i) {
			if (lowers[i] <= max)
				putchar(' ');
			else
				putchar('#');
		}
		for (i = 0; i <= '9' - '0'; ++i) {
			if (digits[i] <= max)
				putchar(' ');
			else
				putchar('#');
		}
		putchar('\n');
	}
	for (i = 'A'; i <= 'Z'; ++i)
		putchar(i);
	for (i = 'a'; i <= 'z'; ++i)
		putchar(i);
	for (i = '0'; i <= '9'; ++i)
		putchar(i);
	putchar('\n');
}
