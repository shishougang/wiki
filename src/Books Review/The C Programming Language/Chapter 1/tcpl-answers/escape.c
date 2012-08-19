#include <stdio.h>

void escape(char s[], char t[]);

void unescape(char s[], char t[]);

main()
{
	char s[100], u[100];
	char t[] = "\t\tA B C\n";

	printf("%s", t);
	escape(s, t);
	printf("%s\n", s);
	unescape(u, s);
	printf("%s", u);

	return 0;
}

void escape(char s[], char t[])
{
	int si, ti;

	for (si = 0, ti = 0; t[ti] != '\0'; ti++) {
		switch (t[ti]) {
			case '\n':
				s[si++] = '\\';
				s[si++] = 'n';
				break;
			case '\t':
				s[si++] = '\\';
				s[si++] = 't';
				break;
			default:
				s[si++] = t[ti];
				break;
		}
	}
	s[si] = '\0';

	return;
}

void unescape(char s[], char t[])
{
	int si, ti;

	for (si = 0, ti = 0; t[ti] != '\0'; si++) {
		if (t[ti] == '\\') {
			ti++;
			if (t[ti] == '\0')
				break;
			switch(t[ti++]) {
				case 'n':
					s[si] = '\n';
					break;
				case 't':
					s[si] = '\t';
					break;
				default:
					s[si] = t[ti];
					break;
			}
		} else {
			s[si] = t[ti++];
		}
	}
	s[si] = '\0';

	return;
}
