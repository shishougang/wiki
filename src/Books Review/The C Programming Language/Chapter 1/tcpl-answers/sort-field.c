#include <stdio.h>
#include <string.h>

#define MAX_FIELDS 10

#define FLAG_DIRECTORY	(0x01 << 0)
#define FLAG_FOLD		(0x01 << 1)
#define FLAG_NUMERIC	(0x01 << 2)
#define FLAG_REVERSE	(0x01 << 3)

int fieldarray[MAX_FIELDS];
unsigned char flagarray[MAX_FIELDS];
int num_fields = 0;

#define MAXLINES 5000		/* max #lines to be sorted */
char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(void *lineptr[], int left, int right,
           int (*comp)(void *, void *));

static char *field_of(char *s, int n);
static isdir(int c);
int compare(char *, char *);
int stringcmp(char *, char *);
int stringcmpi(char *, char *);
int dircmp(char *, char *);
int numcmp(char *, char *);

int numeric = 0;	/* 1 if numeric sort */
int directory = 0;	/* 1 if "directory order" sort */
int reverse = 0;	/* 1 if reverse sort */
int fold = 0;		/* 1 if case-insensitive sort */

/* sort input lines */
main(int argc, char *argv[])
{
	int nlines;			/* number of input lines read */
	int fieldno = 0;
	int i;

	while (--argc > 0) {
		if ((*++argv)[0] == '-') {
			(*argv)++;
			if (isdigit(**argv)) {
				fieldno = 0;
				while (isdigit(*argv[0])) {
					fieldno = fieldno * 10 + *argv[0] - '0';
					(*argv)++;
				}
				if (num_fields >= MAX_FIELDS) {
					printf("error: too many field specifications\n");
					continue;
				}
				fieldarray[num_fields] = fieldno;
				flagarray[num_fields] = 0;
				num_fields++;
			} else {
				while(*argv[0] != '\0') {
					switch (**argv) {
						case 'd':
							if (num_fields > 0)
								flagarray[num_fields - 1] |= FLAG_DIRECTORY;
							else
								directory = 1;
							break;
						case 'f':
							if (num_fields > 0)
								flagarray[num_fields - 1] |= FLAG_FOLD;
							else
								fold = 1;
							break;
						case 'n':
							if (num_fields > 0)
								flagarray[num_fields - 1] |= FLAG_NUMERIC;
							else
								numeric = 1;
							break;
						case 'r':
							if (num_fields > 0)
								flagarray[num_fields - 1] |= FLAG_REVERSE;
							else
								reverse = 1;
							break;
						default:
							printf("error: unknown option `-%c'.\n", **argv);
							break;
					}
					(*argv)++;
				}
			}
		}
	}
	/*
	for (i = 0; i < num_fields; i++) {
		printf("Field %u", fieldarray[i]);
		if (flagarray[i] & FLAG_REVERSE)
			printf(" (reverse)");
		if (flagarray[i] & FLAG_NUMERIC)
			printf(" (numeric)");
		if (flagarray[i] & FLAG_DIRECTORY)
			printf(" (directory)");
		if (flagarray[i] & FLAG_FOLD)
			printf(" (fold)");
		putchar('\n');
	}
	printf("And then");
	if (reverse)
		printf(" (reverse)");
	if (numeric)
		printf(" (numeric)");
	if (directory)
		printf(" (directory)");
	if (fold)
		printf(" (fold)");
	putchar('\n');
	*/

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) compare);
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

static char *field_of(char *s, int n)
{
	while (isspace(*s))
		s++;
	while (--n > 0) {
		while (!isspace(*s)) {
			if (*s == '\0')
				return NULL;
			s++;
		}
	}

	return s;
}

static isdir(int c)
{
	return isalpha(c) || isdigit(c) || isspace(c);
}

int compare_field(char *s1, char *s2, unsigned int flags)
{
	int d;

	if (flags & FLAG_NUMERIC) {
		d = numcmp(s1, s2);
	} else if (flags & FLAG_DIRECTORY) {
		do {
			while (!isdir(*s1) && !isspace(*s1) && *s1 != '\0')
				s1++;
			while (!isdir(*s2) && !isspace(*s2) && *s2 != '\0')
				s2++;
			if (flags & FLAG_FOLD)
				d = toupper(*s1) - toupper(*s2);
			else
				d = *s1 - *s2;
		} while (d == 0 && !isspace(*s1) && !isspace(*s2)
		         && *s1++ != '\0' && *s2++ != '\0');
	} else {
		do {
			if (flags & FLAG_FOLD)
				d = toupper(*s1) - toupper(*s2);
			else
				d = *s1 - *s2;
		} while (d == 0 && !isspace(*s1) && !isspace(*s2)
		         && *s1++ != '\0' && *s2++ != '\0');
	}

	if (flags & FLAG_REVERSE)
		return -d;
	else
		return d;
}

/* compare:  compare s1 and s2 according to the values of the
	external variables numeric, reverse, fold, and directory. */
int compare(char *s1, char *s2)
{
	int i, d;
	char *f1, *f2;

	for (i = 0; i < num_fields; i++) {
		f1 = field_of(s1, fieldarray[i]);
		f2 = field_of(s2, fieldarray[i]);
		d = compare_field(f1, f2, flagarray[i]);
		if (d != 0)
			return d;
	}
	if (numeric)
		d = numcmp(s1, s2);
	else if (directory)
		d = dircmp(s1, s2);
	else
		d = stringcmp(s1, s2);

	if (reverse)
		return -d;
	else
		return d;
}

/* stringcmp:  compare s1 and s2 as strings */
int stringcmp(char *s1, char *s2)
{
	if (fold)
		return stringcmpi(s1, s2);
	else
		return strcmp(s1, s2);
}

/* stringcmpi:  compare s1 and s2 case-insensitively */
int stringcmpi(char *s1, char *s2)
{
	while (toupper(*s1) == toupper(*s2)) {
		if (*s1 == '\0')
			return 0;
		s1++;
		s2++;
	}

	return toupper(*s1) - toupper(*s2);
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
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}
