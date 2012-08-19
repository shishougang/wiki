#include <stdio.h>

#define TEXTWIDTH	40

main()
{
	int c, i, n, column;
	char buffer[TEXTWIDTH + 1];

	column = 0;
	c = getchar();
	while (c != EOF) {
		while (c == '\n') {
			putchar(c);
			column = 0;
			c = getchar();
		}
		n = 0;
		while (column + n < sizeof(buffer) && (c == ' ' || c == '\t')) {
			buffer[n++] = c;
			c = getchar();
		}
		while (column + n < sizeof(buffer)
		       && c != EOF && c != ' ' && c != '\t' && c != '\n') {
			buffer[n++] = c;
			c = getchar();
		}
		if (n + column <= TEXTWIDTH) {
			for (i = 0; i < n; i++)
				putchar(buffer[i]);
			column += n;
			while (c != EOF && c != ' ' && c != '\t' && c != '\n') {
				putchar(c);
				column++;
				c = getchar();
			}
		} else {
			if (column > 0) {
				putchar('\n');
				column = 0;
			}
			for (i = 0; i < n && (buffer[i] == ' ' || buffer[i] == '\t'); i++)
				;
			for ( ; i < n; i++) {
				putchar(buffer[i]);
				column++;
			}
			while (c != EOF && c != ' ' && c != '\t' && c != '\n') {
				putchar(c);
				column++;
				c = getchar();
			}
		}
	}

	return 0;
}
