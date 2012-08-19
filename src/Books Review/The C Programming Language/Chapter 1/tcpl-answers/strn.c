#include <stdlib.h>

char *strncpy(char *s, const char *t, size_t n);
char *strncat(char *s, const char *t, size_t n);
int strncmp(const char *s, const char *t, size_t n);

main()
{
	char s[100] = "Hello";
	char t[100] = "World";

	strncpy(s, t, strlen(t) + 1);
	strncat(s, "Word", 4);
	printf("%s\n", s);
	printf("%s\n", (strncmp(s, t, 5) == 0) ? "true" : "false");

	return 0;
}

char *strncpy(char *s, const char *t, size_t n)
{
	int i;

	for (i = 0; i < n && t[i] != '\0'; i++)
		s[i] = t[i];
	while (i < n)
		s[i++] = '\0';

	return s;
}

char *strncat(char *s, const char *t, size_t n)
{
	char *p;
	int i;

	for (p = s; *p != '\0'; p++)
		;
	for (i = 0; i < n && t[i] != '\0'; i++)
		p[i] = t[i];
	p[i] = '\0';

	return s;
}

int strncmp(const char *s, const char *t, size_t n)
{
	int i;

	for (i = 0; i < n && s[i] == t[i]; i++) {
		if (s[i] == '\0')
			return 0;
	}

	return *s - *t;
}
