#include <time.h>

#ifdef BITFIELDS
#include "stdio-field.h"
#else
#include "stdio.h"
#endif

#define LIMIT 10000000L

main()
{
	clock_t start, end;
	int count;

	start = clock();
	for (count = 0; count < LIMIT; count++)
		getchar();
	end = clock();
#ifdef BITFIELDS
	printf("Using bit-fields.\n");
#else
	printf("Using flags.\n");
#endif
	printf("Got %ld characters in %0.2f seconds.\n", LIMIT,
		(double) (end - start) / CLOCKS_PER_SEC);

	return 0;
}
