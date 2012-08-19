#include <stdio.h>

static int getch(void);
static void ungetch(int c);

void string_literal(void);
void character_constant(void);
void comment(void);

/* remove comments from a C program */
main()
{
	int c;

	while ((c = getch()) != EOF) {
		if (c == '"') {
			ungetch(c);
			string_literal();
		} else if (c == '\'') {
			ungetch(c);
			character_constant();
		} else if (c == '/') {
			c = getch();
			if (c == '*') {
				ungetch(c);
				ungetch('/');
				comment();
			}
		} else {
			putchar(c);
		}
	}

	return 0;
}

void string_literal(void)
{
	int c;

	c = getch();
	if (c != '"')
		return;
	putchar(c);
	while ((c = getch()) != EOF) {
		putchar(c);
		if (c == '\\')
			putchar(getch());
		else if (c == '"')
			break;
	}

	return;
}

void character_constant(void)
{
	int c;

	c = getch();
	if (c != '\'')
		return;
	putchar(c);
	while ((c = getch()) != EOF) {
		putchar(c);
		if (c == '\\')
			putchar(getch());
		else if (c == '\'')
			break;
	}

	return;
}

void comment(void)
{
	int c;

	c = getch();
	if (c != '/') {
		ungetch(c);
		return;
	}
	c = getch();
	if (c != '*') {
		ungetch(c);
		ungetch('/');
		return;
	}
	while ((c = getch()) != EOF) {
		if (c == '*') {
			c = getch();
			if (c == '/')
				break;
			else
				ungetch(c);
		}
	}

	return;
}

#define MAXCHAR 100

static char getchbuf[MAXCHAR];
static int getchindex = 0;

static int getch(void)
{
	if (getchindex > 0)
		return getchbuf[--getchindex];
	else
		return getchar();
}

static void ungetch(int c)
{
	if (getchindex < MAXCHAR && c != EOF)
		getchbuf[getchindex++] = c;

	return;
}
