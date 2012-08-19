#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN	100

enum { NAME, PARENS, BRACKETS, SPECIFIER, QUALIFIER };

void next_line();
int dcl(void);
int dirdcl(void);

int gettoken(void);
int tokentype;			/* type of last token */
char token[MAXTOKEN];	/* last token string */
char name[MAXTOKEN];	/* identifier name */
char datatype[MAXTOKEN];	/* data type = char, int, etc. */
char out[1000];

main()	/* convert declarations to words */
{
	for (;;) {
		datatype[0] = '\0';
		while (gettoken() == SPECIFIER || tokentype == QUALIFIER) {
			strcat(datatype, " ");
			strcat(datatype, token);
		}
		if (tokentype == EOF)
			break;
		if (tokentype == '\n')
			continue;				/* skip blank lines */
		name[0] = '\0';
		out[0] = '\0';
		if (dcl() == 0)	{ /* parse rest of line */
			printf("%s: %s%s\n", name, out, datatype);
		} else {
			printf("%s: %s%s\n", name, out, datatype);
			printf("syntax error\n");
			if (tokentype != '\n')
				next_line();
		}
	}
	return 0;
}

void next_line()
{
	int getch(void);
	int c;

	while ((c = getch()) != '\n' && c != EOF)
		;

	return;
}

/* dcl:  parse a declarator */
int dcl(void)
{
	char tmp[1000];

	tmp[0] = '\0';
	while (tokentype == '*') {
		while (gettoken() == QUALIFIER) {
			strcat(tmp, " ");
			strcat(tmp, token);
		}
		strcat(tmp, " pointer to");
	}
	if (dirdcl() != 0)
		return 1;
	strcat(out, tmp);

	return 0;
}

/* dirdcl:  parse a direct declarator */
int dirdcl(void)
{
	char datatype[1000];
	int type;

	if (tokentype == '(') {			/* ( dcl ) */
		gettoken();
		if (dcl() != 0 || tokentype != ')') {
			printf("error: missing )\n");
			return 1;
		}
	} else if (tokentype == NAME) {	/* variable name */
		if (name[0] == '\0')
			strcpy(name, token);
	} else {
		printf("error: expected name or (dcl)\n");
		return 1;
	}
	type = gettoken();
	if (type == '(') {	/* function */
		strcat(out, " function(");
		gettoken();
		while (tokentype != ')') {
			datatype[0] = '\0';
			while (tokentype == SPECIFIER || tokentype == QUALIFIER) {
				strcat(datatype, " ");
				strcat(datatype, token);
				gettoken();
			}
			if (dcl() != 0)
				return 1;
			strcat(out, datatype);
			if (tokentype == ',') {
				strcat(out, ",");
				gettoken();
			}
		}
		strcat(out, " ) returning");
		gettoken();
	} else {
		while (type == BRACKETS) {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
			type = gettoken();
		}
	}

	return 0;
}

int gettoken(void)	/* return next token */
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
	/*
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
	*/
			return tokentype = '(';
	/*
		}
	*/
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		if (strcmp(token, "auto") == 0
			|| strcmp(token, "register") == 0
			|| strcmp(token, "static") == 0
			|| strcmp(token, "extern") == 0
			|| strcmp(token, "typedef") == 0
			|| strcmp(token, "void") == 0
			|| strcmp(token, "char") == 0
			|| strcmp(token, "short") == 0
			|| strcmp(token, "int") == 0
			|| strcmp(token, "long") == 0
			|| strcmp(token, "float") == 0
			|| strcmp(token, "double") == 0
			|| strcmp(token, "signed") == 0
			|| strcmp(token, "unsigned") == 0)
			return tokentype = SPECIFIER;
		else if (strcmp(token, "const") == 0
		    || strcmp(token, "volatile") == 0)
			return tokentype = QUALIFIER;
		else
			return tokentype = NAME;
	} else
		return tokentype = c;
}

#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)	/* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
