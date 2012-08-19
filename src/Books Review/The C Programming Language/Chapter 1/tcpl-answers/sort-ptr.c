#include <stdio.h>
#include <string.h>

#define MAXLINES 5000		/* max #lines to be sorted */
char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(void *lineptr[], int left, int right,
           int (*comp)(void *, void *));

int stringcmp(char *, char *);
int stringcmpi(char *, char *);
static isdir(int c);
int dircmp(char *, char *);
int numcmp(char *, char *);

int reverse = 0;	/* 1 if reverse sort */
int fold = 0;		/* 1 if case-insensitive sort */

/* sort input lines */
main(int argc, char *argv[])
{
	int nlines;			/* number of input lines read */
	int numeric = 0;	/* 1 if numeric sort */
	int directory = 0;	/* 1 if "directory order" sort */
	int (*comp)(void *, void *);

	while (--argc > 0) {
		if ((*++argv)[0] == '-') {
			while(*++argv[0] != '\0') {
				switch (**argv) {
					case 'd':
						directory = 1;
						break;
					case 'f':
						fold = 1;
						break;
					case 'n':
						numeric = 1;
						break;
					case 'r':
						reverse = 1;
						break;
					default:
						printf("error: unknown option `-%c'.\n", **argv);
						break;
				}
			}
		}
	}
	if (numeric)
		comp = (int (*)(void *, void *)) numcmp;
	else if (directory)
		comp = (int (*)(void *, void *)) dircmp;
	else
		comp = (int (*)(void *, void *)) stringcmp;
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort((void **) lineptr, 0, nlines-1, comp);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000	/* max length of any input line */
int getline(char *, int);
char *alloc(int);

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';	/* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;

	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

/* getline:  read a line into s, return length */
int getline(char s[], int lim)
{
	int c, i;

	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	for ( ; c != EOF && c != '\n'; ++i)
		c = getchar();
	return i;
}

#define ALLOCSIZE 10000	/* size of available space */

static char allocbuf[ALLOCSIZE];	/* storage for alloc */
static char *allocp = allocbuf;		/* next free position */

char *alloc(int n)	/* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) {	/* it fits */
		allocp += n;
		return allocp - n;	/* old p */
	} else
		return 0;
}

void afree(char *p)	/* free storage pointed to by p */
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

/* qsort:  sort v[left]...v[right] into increasing order */
void qsort(void *v[], int left, int right,
           int (*comp)(void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)	/* do nothing if array contains */
		return;			/* fewer than two elements */
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1, comp);
	qsort(v, last+1, right, comp);
}

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* stringcmp:  compare s1 and s2 as strings */
int stringcmp(char *s1, char *s2)
{
	extern int reverse;
	extern int fold;
	int d;

	if (fold)
		return stringcmpi(s1, s2);

	d = strcmp(s1, s2);

	return (reverse) ? -d : d;
}

/* stringcmpi:  compare s1 and s2 case-insensitively */
int stringcmpi(char *s1, char *s2)
{
	extern int reverse;
	int d;

	while (toupper(*s1) == toupper(*s2)) {
		if (*s1 == '\0')
			return 0;
		s1++;
		s2++;
	}
	d = toupper(*s1) - toupper(*s2);

	return (reverse) ? -d : d;
}

static isdir(int c)
{
	return isalpha(c) || isdigit(c) || isspace(c);
}

/* dircmp:  compare s1 and s2 in "directory order" */
int dircmp(char *s1, char *s2)
{
	int d;

	do {
		while (!isdir(*s1) && *s1 != '\0')
			s1++;
		while (!isdir(*s2) && *s2 != '\0')
			s2++;
		if (fold)
			d = toupper(*s1) - toupper(*s2);
		else
			d = *s1 - *s2;
	} while (d == 0 && *s1++ != '\0' && *s2++ != '\0');

	return d;
}

/* numcmp:  compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
	extern double atof(const char *);
	extern int reverse;
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return (reverse) ? 1 : -1;
	else if (v1 > v2)
		return (reverse) ? -1 : 1;
	else
		return 0;
}
