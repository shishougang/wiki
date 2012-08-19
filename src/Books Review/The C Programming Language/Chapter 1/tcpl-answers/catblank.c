#include <stdio.h>

/* copy input to output, replacing each string of one
	or more blanks by a single blank */
main()
{
	int c, last;

	last = EOF;
	while ((c = getchar()) != EOF) {
		if (c != ' ')
			putchar(c);
		if (c == ' ') {
			if (last != ' ')
				putchar(c);
		}
		last = c;
	}
}
