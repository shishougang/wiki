#include <stdio.h>
#include <stdlib.h>		/* for atof() */

#define MAXOP	100		/* max size of operand or operator */
#define NUMBER	'0'		/* signal that a number was found */

int getop(char s[], char *argv[]);
void push(double f);
double pop(void);

/* command-line reverse Polish calculator */
main(int argc, char *argv[])
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s, ++argv)) != EOF) {
		switch(type) {
		case NUMBER:
			push(atof(s));
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
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	printf("\t%.8g\n", pop());
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

/* getop:  get next operator or numeric operand */
int getop(char s[], char *argv[])
{
	int i;
	char *p;

	if (*argv == NULL)
		return EOF;
	p = *argv;
	s[0] = *p;
	s[1] = '\0';
	if (!isdigit(*p) && *p != '.')
		return *p;	/* not a number */
	i = 0;
	if (isdigit(*p))	/* collect integer part */
		while (isdigit(s[++i] = *++p))
			;
	if (*p == '.')	/* collect fraction part */
		while (isdigit(s[++i] = *++p))
			;
	s[i] = '\0';
	return NUMBER;
}
