#include <stdio.h>

void expand(char s1[], char s2[]);

main()
{
	char *tests[] = { "a-z", "a-b-c", "a-z0-9", "-a-z", "-", "@-c",
		"z-a", "z-abc", "z-a-c", "b-b", "b-b-b-" };
	char expanded[1000];
	int i;

	for (i = 0; i < sizeof(tests) / sizeof(*tests); i++) {
		expand(tests[i], expanded);
		printf("%s => %s\n", tests[i], expanded);
	}

	return 0;
}

/* expand:  expand shorthand notation like a-z in s1 into the equivalent
	complete list abc...xyz in s2. A leading or trailing - is taken
	literally. */
void expand(char s1[], char s2[])
{
	int i, j;
	char cur, next;

	for (i = 0, j = 0; s1[i] != '\0'; i++) {
		cur = s1[i];
		next = s1[i + 1];
		if (next == '-' && s1[i + 2] != '\0') {
			if (cur < s1[i + 2]) {
				while (cur < s1[i + 2]) {
					s2[j++] = cur;
					cur++;
				}
			} else {
				while (cur > s1[i + 2]) {
					s2[j++] = cur;
					cur--;
				}
			}
			i++;
		} else {
			s2[j++] = cur;
		}
	}
	s2[j] = '\0';

	return;
}
