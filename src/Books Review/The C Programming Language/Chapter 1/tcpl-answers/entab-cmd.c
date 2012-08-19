#include <stdio.h>

#define MAXTABSTOPS	50

int next_tabstop(int column);
void print_blanks(int n, int column);

int tabstops[MAXTABSTOPS] = { 0 };
int thereafter = 0;

main(int argc, char *argv[])
{
	int c, i, column, blank_column, num_blanks;
	int num_tabstops, tabstop, plus_flag, minus_flag;
	char *p;

	/* num_tabstops is the number of tabstops read from the
	   command line. */
	num_tabstops = 0;
	for (i = 1; i < argc; i++) {
		plus_flag = 0;
		minus_flag = 0;
		p = argv[i];
		if (*p == '+') {
			plus_flag = 1;
			p++;
		} else if (*p == '-') {
			minus_flag = 1;
			p++;
		}
		tabstop = 0;
		for (; isdigit(*p); p++)
			tabstop = tabstop * 10 + *p - '0';
		if (*p != '\0' || tabstop == 0) {
			printf("Illegal tabstop %s ignored.\n", argv[i]);
			continue;
		}
		if (plus_flag) {
			thereafter = tabstop;
		} else if (minus_flag) {
			tabstops[0] = tabstop;
			num_tabstops = 1;
		} else if (num_tabstops >= MAXTABSTOPS) {
			printf("Too many tabstops: %s.\n", argv[i]);
			continue;
		} else {
			tabstops[num_tabstops++] = tabstop;
		}
	}
	if (thereafter == 0) {
		if (num_tabstops > 0) {
			num_tabstops--;
			thereafter = tabstops[num_tabstops];
			tabstops[num_tabstops] = 0;
		} else {
			thereafter = 8;
		}
	}

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
			num_blanks += next_tabstop(column);
			column += next_tabstop(column);
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

int next_tabstop(int column)
{
	int i;

	for (i = 0; i < MAXTABSTOPS && tabstops[i] != 0
	            && column >= tabstops[i]; i++)
		column -= tabstops[i];
	if (i < MAXTABSTOPS && tabstops[i] != 0)
		column = tabstops[i] - column;
	else
		column = thereafter - column % thereafter;

	return column;
}

void print_blanks(int n, int column)
{
	/* Skip over tab stops. */
	while (n > 1 && n >= next_tabstop(column)) {
		putchar('\t');
		n -= next_tabstop(column);
		column += next_tabstop(column);
	}
	/* Fill out the rest with blanks. */
	while (n > 0) {
		putchar(' ');
		n--;
	}

	return;
}
