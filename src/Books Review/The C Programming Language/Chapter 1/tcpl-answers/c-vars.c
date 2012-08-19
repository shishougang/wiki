#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode {			/* the tree node: */
	char *word;				/* points to the text */
	int count;				/* number of occurrences */
	struct tnode *left;		/* left child */
	struct tnode *right;	/* right child */
};

struct tnode *addtree(struct tnode *, char *);
char *treeprint(struct tnode *, char *, int);
int getvar(char *, int);

main(int argc, char *argv[])
{
	struct tnode *root;
	char var[MAXWORD];
	int i, n;
	char *p;

	n = 6;
	for (i = 1; i < argc; i++) {
		p = argv[i];
		if (*p == '-') {
			for (p++; *p != '\0'; p++) {
				if (*p == 'n' && *(p + 1) == '\0' && argc - i > 1) {
					i++;
					n = 0;
					for (p = argv[i]; *p != '\0'; p++) {
						if (isdigit(*p)) {
							n = n * 10 + (*p - '0');
						} else {
							printf("Usage: %s [-n NUM]\n", argv[0]);
							return 1;
						}
					}
					break;
				} else {
					printf("Usage: %s [-n NUM]\n", argv[0]);
					return 1;
				}
			}
		} else {
			printf("Usage: %s [-n NUM]\n", argv[0]);
			return 1;
		}
	}
	root = NULL;
	while (getvar(var, MAXWORD) != EOF)
		root = addtree(root, var);
	treeprint(root, NULL, n);
	return 0;
}

struct tnode *talloc(void);

/* addtree:  add a node with w, at of below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {	/* a new word has arrived */
		p = talloc();	/* make a new node */
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;		/* repeated word */
	else if (cond < 0)	/* less than into left subtree */
		p->left = addtree(p->left, w);
	else			/* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

char *treeprint(struct tnode *root, char *s, int n)
{
	char *t;

	if (root != NULL) {
		t = treeprint(root->left, s, n);
		if (t != NULL && strncmp(t, root->word, n) != 0)
			printf("\n");
		printf("%s\n", root->word);
		return treeprint(root->right, root->word, n);
	} else {
		return s;
	}
}

#include <stdlib.h>

/* talloc:  make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

static int isletter(int c)
{
	return isalpha(c) || c == '_';
}

/* getvar:  get next variable name from input */
int getvar(char *var, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *v = var;

	while ((c = getch()) != EOF) {
		if (c == '\'') {
			c = getch();
			if (c == '\\')
				c = getch();
			c = getch();
		} else if (c == '"') {
			while ((c = getch()) != '"' && c != EOF) {
				if (c == '\\')
					c = getch();
			}
		} else if (c == '/') {
			if ((c = getch()) == '*') {
				for (;;) {
					c = getch();
					if (c == EOF)
						break;
					if (c == '*') {
						c = getch();
						if (c == '/')
							break;
						else
							ungetch(c);
					}
				}
			} else {
				ungetch(c);
			}
		} else if (isletter(c)) {
			*v++ = c;
			for ( ; --lim > 0; v++) {
				if (!isletter(*v = getch()) && !isdigit(*v)) {
					ungetch(*v);
					break;
				}
			}
			v[0] = '\0';
			return var[0];
		}
	}
	return EOF;
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
