#include <stdio.h>

/* copy input to output, replacing tabs, backspaces and backslashes
	by their escape sequences */
main()
{
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			putchar('\\');
			c = 't';
		}
		if (c == '\b') {
			putchar('\\');
			c = 'b';
		}
		if (c == '\\') {
			putchar('\\');
			c = '\\';
		}
		putchar(c);
	}
}
