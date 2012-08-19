#include <stdio.h>
#define MAXLINE 1000	/* maximum input line size */
#define THRESHOLD 80

int getline(char line[], int maxline);

/* print lines longer than 80 characters */
main()
{
	int len;			/* line length */
	char line[MAXLINE];		/* input line */

	while ((len = getline(line, MAXLINE)) > 0)
		if (len > THRESHOLD)
			printf("%s", line);
	return 0;
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
