#include <stdio.h>

#define MAXLINES	5000	/* Maximum number of lines to display. */

char *lineptr[MAXLINES];	/* Pointer to input lines. */

#define BUFFERSIZE 1000

#define DEFAULT_LAST 10

int readlines(char *lineptr[], char *buffer, int maxlines);
static void unwrap(char *buffer, int index);
static void reverse(char *lineptr[], int nlines);

main(int argc, char *argv[])
{
	int nlines, i, last, offset;
	char buffer[BUFFERSIZE];
	char *p;

	last = DEFAULT_LAST;
	for (i = 0; i < argc; i++) {
		p = argv[i];
		if (*p++ == '-') {
			last = 0;
			while (isdigit(*p)) {
				last = last * 10 + *p - '0';
				p++;
			}
			if (*p != '\0') {
				printf("invalid argument: %s\n", argv[i]);
				last = DEFAULT_LAST;
			}
		}
	}

	nlines = readlines(lineptr, buffer, MAXLINES);
	if (nlines < 0) {
		printf("error: input too big to process\n");
		return 1;
	}
	if (nlines < last) {
		printf("error: only printing the last %d lines.\n", nlines);
		offset = 0;
	} else if (last > MAXLINES) {
		offset = nlines - MAXLINES;
	} else {
		offset = nlines - last;
	}
	for (i = 0; i < nlines && i < last; i++)
		printf("%s\n", lineptr[offset + i]);

	return 0;
}

int readlines(char *lineptr[], char *buffer, int maxlines)
{
	int c, nlines;
	int wrapped;
	char *p;

	/* The input lines are stored end-to-end in the buffer, with
	   newlines converted to null bytes. */
	wrapped = 0;
	p = buffer;
	while ((c = getchar()) != EOF) {
		if (c == '\n')
			*p = '\0';
		else
			*p = c;
		p++;
		if (p >= buffer + BUFFERSIZE) {
			p = buffer;
			wrapped = 1;
		}
	}
	/* Rearrange the buffer so the oldest byte comes first. */
	if (wrapped) {
		unwrap(buffer, p - buffer);
		p = buffer + BUFFERSIZE;
	}
	p--;
	*p = '\0';
	nlines = 0;
	while (p >= buffer && nlines < maxlines) {
		p--;
		if (*p == '\0')
			lineptr[nlines++] = p + 1;
	}
	reverse(lineptr, nlines);

	return nlines;
}

static void unwrap(char *buffer, int index)
{
	char work[BUFFERSIZE];

	memmove(work, buffer + index, BUFFERSIZE - index);
	memmove(work + BUFFERSIZE - index, buffer, index);
	memmove(buffer, work, BUFFERSIZE);

	return;
}

static void reverse(char *lineptr[], int nlines)
{
	char *tmp;
	int i;

	for (i = 0; i < nlines / 2; i++) {
		tmp = lineptr[i];
		lineptr[i] = lineptr[nlines - i - 1];
		lineptr[nlines - i - 1] = tmp;
	}

	return;
}
