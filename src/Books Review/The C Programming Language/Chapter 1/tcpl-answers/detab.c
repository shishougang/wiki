#include <stdio.h>

#define TABSTOP	8

main()
{
	int c, i, column;

	column = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			for (i = 0; i < TABSTOP - column % TABSTOP; i++)
				putchar(' ');
			column += TABSTOP - column % TABSTOP;
		} else if (c == '\n') {
			putchar(c);
			column = 0;
		} else {
			putchar(c);
			column++;
		}
	}

	return 0;
}
