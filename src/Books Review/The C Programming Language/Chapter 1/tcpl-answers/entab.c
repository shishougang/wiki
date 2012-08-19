#include <stdio.h>

#define TABSTOP	8

void print_blanks(int n, int column);

main()
{
	int c, column, blank_column, num_blanks;

	column = 0;
	blank_column = 0;
	num_blanks = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (num_blanks == 0)
				blank_column = column;
			num_blanks++;
			column++;
		} else if (c == '\t') {
			if (num_blanks == 0)
				blank_column = column;
			num_blanks += TABSTOP - column % TABSTOP;
			column += TABSTOP - column % TABSTOP;
		} else if (c == '\n') {
			if (num_blanks > 0)
				print_blanks(num_blanks, blank_column);
			num_blanks = 0;
			putchar(c);
			column = 0;
		} else {
			if (num_blanks > 0)
				print_blanks(num_blanks, blank_column);
			num_blanks = 0;
			putchar(c);
			column++;
		}
	}

	return 0;
}

void print_blanks(int n, int column)
{
	/* Get to the next tab stop. */
	if (TABSTOP - column % TABSTOP > 1
	    && TABSTOP - column % TABSTOP <= n) {
		putchar('\t');
		n -= TABSTOP - column % TABSTOP;
	}
	/* Skip over full tab stops. */
	while (n >= TABSTOP) {
		putchar('\t');
		n -= TABSTOP;
	}
	/* Fill out the rest with blanks. */
	while (n > 0) {
		putchar(' ');
		n--;
	}

	return;
}
