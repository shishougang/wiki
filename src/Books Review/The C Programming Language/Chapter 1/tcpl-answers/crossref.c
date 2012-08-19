#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *noise[] = {
	"a", "and", "of", "the"
};

char **binsearch(char *key, char *array[], int n);
struct node *node_add(struct node *p, char *word, int n);
void treeprint(struct node *p);
int getword(char *word, int lim);

#define MAXWORD 100

struct line_node {
	int num;
	struct line_node *next;
};

struct node {
	char *word;
	struct line_node *lines;
	struct node *left;
	struct node *right;
};

main()
{
	struct node *root;
	int line;
	char word[MAXWORD];

	root = NULL;
	line = 1;
	for (;;) {
		line += getword(word, MAXWORD);
		if (word[0] == '\0')
			break;
		if (binsearch(word, noise, sizeof(noise) / sizeof(*noise)) == NULL)
			root = node_add(root, word, line);
	}
	treeprint(root);

	return 0;
}

char **binsearch(char *key, char *array[], int n)
{
	int low, mid, high;
	int comp;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		comp = strcmp(key, array[mid]);
		if (comp < 0)
			high = mid - 1;
		else if (comp > 0)
			low = mid + 1;
		else
			return array + mid;
	}

	return NULL;
}

struct line_node *line_node_alloc(void);
struct node *node_alloc(void);

struct node *node_add(struct node *p, char *word, int n)
{
	int cond;
	struct line_node *ptr;

	if (p == NULL) {
		p = node_alloc();
		p->word = strdup(word);
		p->left = p->right = NULL;
		p->lines = line_node_alloc();
		p->lines->num = n;
		p->lines->next = NULL;
	} else if ((cond = strcmp(word, p->word)) == 0) {
		for (ptr = p->lines; ptr->next != NULL; ptr = ptr->next)
			;
		ptr->next = line_node_alloc();
		ptr->next->num = n;
		ptr->next->next = NULL;
	} else if (cond < 0) {
		p->left = node_add(p->left, word, n);
	} else {
		p->right = node_add(p->right, word, n);
	}
	return p;
}

void treeprint(struct node *p)
{
	struct line_node *line;

	if (p != NULL) {
		treeprint(p->left);
		printf("%s", p->word);
		for (line = p->lines; line != NULL; line = line->next)
			printf(" %d", line->num);
		printf("\n");
		treeprint(p->right);
	}
}

struct line_node *line_node_alloc(void)
{
	return malloc(sizeof(struct line_node));
}

struct node *node_alloc(void)
{
	return malloc(sizeof(struct node));
}

int getch(void);
void ungetch(int);

int getword(char *word, int lim)
{
	int c, lines;
	char *p;

	lines = 0;
	while (!isalpha(c = getch()) && c != EOF) {
		if (c == '\n')
			lines++;
	}
	p = word;
	while (lim-- > 0 && isalpha(c)) {
		*p++ = c;
		c = getch();
	}
	*p = '\0';

	return lines;
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
