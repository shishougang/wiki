#include <stdio.h>

#define IN	1
#define OUT	0
#define MAXLENGTH	10

/* print a histogram of the lengths of words in the input */
main()
{
	int c, i, j, length, state;
	int lengths[MAXLENGTH];
	int nlong;
	/* lengths[0] is the number of words of length 1. nlong is the number
	   of words whose length is greater than MAXLENGTH. */

	for (i = 0; i < MAXLENGTH; i++)
		lengths[i] = 0;
	nlong = 0;

	state = OUT;
	length = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (state == IN) {
				if (length < MAXLENGTH)
					++lengths[length - 1];
				else
					++nlong;
			}
			length = 0;
		} else {
			state = IN;
			++length;
		}
	}

	for (i = 0; i < MAXLENGTH; i++) {
		printf(" %2d: ", i + 1);
		for (j = 0; j < lengths[i]; j++)
			putchar('#');
		putchar('\n');
	}
	printf(">%2d: ", MAXLENGTH);
	for (j = 0; j < nlong; j++)
		putchar('#');
	putchar('\n');
}
