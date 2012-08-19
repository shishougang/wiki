#include <math.h>		/* for fmod() */
#include <stdio.h>
#include <stdlib.h>		/* for atof() */
#include <string.h>

#define MAXOP	100		/* max size of operand or operator */
#define NUMBER	'0'		/* signal that a number was found */
#define WORD	'a'		/* signal that a word was found */
#define VARIABLE	'A'	/* signal that a variable was found */

int getop(char []);
void push(double);
double pop(void);
void clear(void);

/* reverse Polish calculator */
main()
{
	int i, type;
	double op1, op2;
	char s[MAXOP];
	double variables[27];

	for (i = 0; i < sizeof(variables) / sizeof(*variables); i++)
		variables[i] = 0.0;

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case VARIABLE:
				/* a variable name pushes an index on the stack. The index
					is used by set and ref to access the value of the variable. */
				if (isupper(s[0]))
					push(s[0] - 'A');
				else if (s[0] == '$')
					push(26.0);
				else
					printf("error: unknown variable %s\n", s);
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if (op2 != 0.0)
					push(fmod(pop(), op2));
				else
					printf("error: zero modulus\n");
				break;
			case '\n':
				variables[26] = pop();
				printf("\t%.8g\n", variables[26]);
				break;
			case WORD:
				if (strcmp(s, "clear") == 0) {
					clear();
				} else if (strcmp(s, "cos") == 0) {
					push(cos(pop()));
				} else if (strcmp(s, "dup") == 0) {
					op1 = pop();
					push(op2);
					push(op2);
				} else if (strcmp(s, "exp") == 0) {
					push(exp(pop()));
				} else if (strcmp(s, "log") == 0) {
					push(log(pop()));
				} else if (strcmp(s, "pow") == 0) {
					op2 = pop();
					push(pow(pop(), op2));
				} else if (strcmp(s, "print") == 0) {
					variables[26] = pop();
					push(variables[26]);
					printf("\t%.8g\n", variables[26]);
				} else if (strcmp(s, "ref") == 0) {
					/* ref pushes the value of the variable whose index
						is on the stack */
					push(variables[(int) pop()]);
				} else if (strcmp(s, "set") == 0) {
					/* set sets the variable with the index on the stack */
					op2 = pop();
					variables[(int) op2] = pop();
				} else if (strcmp(s, "sin") == 0) {
					push(sin(pop()));
				} else if (strcmp(s, "sqrt") == 0) {
					push(sqrt(pop()));
				} else if (strcmp(s, "swap") == 0) {
					op2 = pop();
					op1 = pop();
					push(op2);
					push(op1);
				} else if (strcmp(s, "tan") == 0) {
					push(tan(pop()));
				} else {
					printf("error: unknown command %s\n", s);
				}
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

#define MAXVAL	100		/* maximum depth of val stack */

int sp = 0;				/* next free stack position */
double val[MAXVAL];		/* value stack */

/* push:  push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop:  pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

void clear(void)
{
	sp = 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
	int i, c, type;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	/* each non-alphanumeric, single-character operator
		is its own type */
	if (!isalpha(c) && !isdigit(c) && c != '.' && c != '-'
	    && c != '$')
		return c;
	if (isupper(c) || c == '$')
		return VARIABLE;
	if (c == '-') {
		c = getch();
		ungetch(c);
		if (!isdigit(c) && c != '.')
			/* subtraction operator */
			return '-';
	}
	i = 0;
	if (isdigit(c) || c == '.') {
		/* collect integer part */
		type = NUMBER;
		while (isdigit(s[++i] = c = getch()))
			;
		if (c == '.')		/* collect fraction part */
			while (isdigit(s[++i] = c = getch()))
				;
	} else {
		/* word operator */
		type = WORD;
		while ((s[++i] = c = getch()) != ' ' && c != '\t'
		       && !isdigit(c) && c != '\n' && c != EOF)
			;
	}
	s[i] = '\0';
	ungetch(c);
	return type;
}

/* alternate getop for exercise 4-10 */
#if 0
int getline(char s[], int lim);

#define MAXLINE 1000

char line[MAXLINE];
int linep = -1;

int getop(char s[])
{
	int i, c, type;

	if (linep == -1 || line[linep] == '\0') {
		getline(line, MAXLINE);
		linep = 0;
		if (line[0] == '\0')
			return EOF;
	}
	while ((s[0] = c = line[linep++]) == ' ' || c == '\t')
		;
	s[1] = '\0';
	/* each non-alphanumeric, single-character operator
		is its own type */
	if (!isalpha(c) && !isdigit(c) && c != '.' && c != '-'
	    && c != '$')
		return c;
	if (isupper(c) || c == '$')
		return VARIABLE;
	if (c == '-') {
		c = line[linep];
		if (!isdigit(c) && c != '.')
			/* subtraction operator */
			return '-';
	}
	i = 0;
	if (isdigit(c) || c == '.') {
		/* collect integer part */
		type = NUMBER;
		while (isdigit(s[++i] = c = line[linep++]))
			;
		if (c == '.')		/* collect fraction part */
			while (isdigit(s[++i] = c = line[linep++]))
				;
	} else {
		/* word operator */
		type = WORD;
		while ((s[++i] = c = line[linep++]) != ' ' && c != '\t'
		       && !isdigit(c) && c != '\n' && c != '\0')
			;
	}
	s[i] = '\0';
	linep--;
	return type;
}
#endif

#define BUFSIZE	100

char buf[BUFSIZE];	/* buffer for ungetch */
int  bufp = 0;		/* next free position in buf */

int getch(void)	/* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (c == EOF)
		return;
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void ungets(char s[]) /* push string back on input */
{
	size_t length;

	length = strlen(s);
	if (bufp + length > BUFSIZE)
		printf("ungets: too many characters\n");
	else {
		while (length-- > 0)
			buf[bufp++] = s[length];
	}
}

/* Alternate getch and ungetch for exercise 4-8 */
/*
int getch_char = EOF;

int getch(void)
{
	int ch;

	if (getch_char == EOF) {
		ch = getchar();
	} else {
		ch = getch_char;
		getch_char = EOF;
	}

	return ch;
}

void ungetch(int c)
{
	if (getch_char != EOF)
		printf("ungetch: too many characters\n");
	else
		getch_char = c;
}
*/

/* getline:  get line into s, return length */
int getline(char s[], int lim)
{
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
