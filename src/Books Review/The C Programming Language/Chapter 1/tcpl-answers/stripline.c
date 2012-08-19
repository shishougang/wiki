#include <stdio.h>
#define MAXLINE 1000	/* maximum input line size */
#define THRESHOLD 80

int getline(char line[], int maxline);

/* remove trailing blanks and tabs from each line of input
	and remove blank lines */
main()
{
	int len;			/* line length */
	char line[MAXLINE];		/* input line */

	while ((len = getline(line, MAXLINE)) > 0) {
		if (line[0] != '\n' || 1) {
			stripline(line);
			printf("%s", line);
		}
	}

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

/* stripline:  remove trailing whitespace from s,
	return new length */
int stripline(char s[])
{
	int i, end;

	end = 0;
	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			end = i + 1;
	}
	if (i >= 1 && s[i - 1] == '\n') {
		s[end] = '\n';
		s[end + 1] = '\0';
	} else {
		s[end] = '\0';
	}

	return end;
}
