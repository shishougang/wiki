#include <stdio.h>

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

void reverse(char s[])
{
	int i, length;
	char tmp;

	length = 0;
	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] != '\n')
			length = i + 1;
	}
	for (i = 0; i < length / 2; i++) {
		tmp = s[i];
		s[i] = s[length - i - 1];
		s[length - i - 1] = tmp;
	}
}
