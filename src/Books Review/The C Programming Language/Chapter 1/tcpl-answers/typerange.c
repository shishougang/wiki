#include <stdio.h>
#include <float.h>
#include <limits.h>

main()
{
	char c, char_min, char_max;
	short s, short_min, short_max;
	int i, int_min, int_max;
	long l, long_min, long_max;
	long low, mid, high;

	low = 0;
	high = 1;
	while ((char) high >= 0) {
		low = high;
		high = high * 2;
	}
	while (low < high) {
		mid = (low + high) / 2;
		if ((char) mid > 0)
			low = mid + 1;
		else
			high = mid;
	}
	char_min = high;
	char_max = high - 1;
	printf("char:  %d..%d by standard library and"
	       " %d..%d by computation.\n",
	       CHAR_MIN, CHAR_MAX, char_min, char_max);
	low = 0;
	high = 1;
	while ((short) high >= 0) {
		low = high;
		high = high * 2;
	}
	while (low < high) {
		mid = (low + high) / 2;
		if ((short) mid > 0)
			low = mid + 1;
		else
			high = mid;
	}
	short_min = high;
	short_max = high - 1;
	printf("short: %d..%d by standard library and"
	       " %d..%d by computation.\n",
	       SHRT_MIN, SHRT_MAX, short_min, short_max);
	int_min = 1;
	while (int_min >= 0)
		int_min <<= 1;
	int_max = int_min - 1;
	printf("int:   %d..%d by standard library and"
	       " %d..%d by computation.\n",
	       INT_MIN, INT_MAX, int_min, int_max);
	long_min = 1;
	while (long_min >= 0)
		long_min <<= 1;
	long_max = long_min - 1;
	printf("long:  %ld..%ld by standard library and"
	       " %ld..%ld by computation.\n",
	       LONG_MIN, LONG_MAX, long_min, long_max);
	printf("float: %f..%f by standard library.\n",
	       -FLT_MAX, FLT_MAX);
	printf("double: %lf..%lf by standard library.\n",
	       -DBL_MAX, DBL_MAX);

	return 0;
}
