#include <ctype.h>
#include <stdio.h>

unsigned int htoi(char s[]);

main()
{
	char *tests[] = { "0001", "0xF", "0XDEEF", "ABC", "0xDAVID" };
	int i;

	for (i = 0; i < sizeof(tests) / sizeof(*tests); i++)
		printf("%s\t%u\n", tests[i], htoi(tests[i]));

	return 0;
}

unsigned int htoi(char s[])
{
	int i, h;

	h = 0;
	i = 0;
	if (s[0] == '0') {
		if (s[1] == 'X' || s[1] == 'x')
			i += 2;
	}
	while (s[i] != '\0') {
		h = h * 16;
		if (isdigit(s[i]))
			h += s[i] - '0';
		else if (s[i] >= 'A' && s[i] <= 'F')
			h += s[i] - 'A' + 10;
		else if (s[i] >= 'a' && s[i] <= 'f')
			h += s[i] - 'a' + 10;
		else
			return (unsigned int) -1;
		i++;
	}

	return h;
}
