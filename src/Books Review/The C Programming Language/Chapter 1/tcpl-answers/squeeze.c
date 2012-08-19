#include <stdio.h>

void squeeze(char s1[], char s2[]);

main()
{
	char test[] = "squeeze";
	char remove[] = "qe";

	squeeze(test, remove);
	printf("%s", test);

	return 0;
}

void squeeze(char s1[], char s2[])
{
	int i1, i2, j;

	for (i1 = j = 0; s1[i1] != '\0'; i1++) {
		for (i2 = 0; s2[i2] != '\0'; i2++) {
			if (s2[i2] == s1[i1])
				break;
		}
		if (s2[i2] == '\0')
			s1[j++] = s1[i1];
	}
	s1[j] = '\0';
}
