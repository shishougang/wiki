#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

struct tnode {			/* the tree node: */
	char *word;				/* points to the text */
	int count;				/* number of occurrences */
	struct tnode *left;		/* left child */
	struct tnode *right;	/* right child */
};

struct tnode *addtree(struct tnode *, char *);
static int treecount(struct tnode *);
static struct tnode **tree_flatten(struct tnode *p, struct tnode **list);
static int tnode_compare_count(const struct tnode **a, const struct tnode **b);
void treeprint(struct tnode *p);
int getword(char *, int);

/* word frequency count */
main()
{
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);
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

/* treecount:  count the total number of nodes in p */
static int treecount(struct tnode *p)
{
	if (p == NULL)
		return 0;

	return 1 + treecount(p->left) + treecount(p->right);
}

/* tree_flatten:  turn the tree p into a flat in-order list */
static struct tnode **tree_flatten(struct tnode *p, struct tnode **list)
{
	if (p != NULL) {
		list = tree_flatten(p->left, list);
		*(list++) = p;
		return tree_flatten(p->right, list);
	} else {
		return list;
	}
}

static int tnode_compare_count(const struct tnode **a, const struct tnode **b)
{
	return (**b).count - (**a).count;
}

/* treeprint:  print nodes of tree p in decreasing order by count */
void treeprint(struct tnode *p)
{
	struct tnode **list;
	int i, n;

	n = treecount(p);
	list = malloc(sizeof(struct tnode *) * n);
	tree_flatten(p, list);
	qsort(list, n, sizeof(struct tnode *),
		(int (*)(const void *, const void *)) tnode_compare_count);
	for (i = 0; i < n; i++)
		printf("%4d %s\n", list[i]->count, list[i]->word);
	free(list);

	return;
}

/* talloc:  make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
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

#if 0
char *strdup(char *);

char *strdup(char *s)	/* make a duplicate of s */
{
	char *p;

	p = (char *) malloc(strlen(s)+1);	/* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}
#endif
