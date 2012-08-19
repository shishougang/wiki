#include <stdio.h>

void qsort(int v[], int left, int right);
void printarray(const int v[], size_t length);

main()
{
	int v[10] = { 5, 7, 3, 8, 2, 4, 1, 9, 0, 6 };
	int i;

	printarray(v, 10);
	qsort(v, 0, 9);
	printarray(v, 10);

	return 0;
}

/* qsort:  sort v[left]...v[right] into increasing order */
void qsort(int v[], int left, int right)
{
	int i, last;
	extern void swap(int v[], int left, int right);

	if (left >= right)	/* do nothing if array contains */
		return;			/* fewer than two elements */
	swap(v, left, (left + right)/2);	/* move partition elem */
	last = left;						/* to v[0] */
	for (i = left+1; i <= right; i++)	/* partition */
		if (v[i] < v[left])
			swap(v, ++last, i);
	swap(v, left, last);	/* restore partition elem */
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

/* swap:  interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void printarray(const int v[], size_t length)
{
	int i;

	printf("{ ");
	i = 0;
	while (i < length) {
		printf("%d", v[i]);
		i++;
		if (i < length)
			printf(", ");
	}
	printf(" }\n");

	return;
}
