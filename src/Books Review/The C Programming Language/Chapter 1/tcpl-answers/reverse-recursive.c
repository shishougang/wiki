#include <stdio.h>
#include <string.h>

#define MAXLINE	1000

int getline(char s[], int lim);
void reverse(char s[]);

main()
{
	char line[MAXLINE];
	int len;

	while ((len = getline(line, MAXLINE)) > 0) {
		reverse(line);
		printf("%s", line);
	}

	return 0;
}

/* reverse:  reverse a string in place */
void reverse(char s[])
{
	int c, i, l;

	l = strlen(s);
	if (l > 1) {
		/* Reverse the rest of the string. */
		reverse(s + 1);
		/* Put the first character at the end. */
		c = s[0];
		for (i = 1; i < l; i++)
			s[i - 1] = s[i];
		s[l - 1] = c;
	}
}

int getline(char s[], int lim)
{
	int c, i;

	c = '\0';
	i = 0;
	while (i < lim - 1) {
		c = getchar();
		if (c == EOF || c == '\n')
			break;
		s[i++] = c;
	}
	if (c == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	while (c != EOF && c != '\n') {
		c = getchar();
		i++;
	}

	return i;
}
