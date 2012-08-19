#include <stdio.h>
#include <time.h>

int binsearch(int x, int v[], int n);

int altbinsearch(int x, int v[], int n);

#define ARRAY_SIZE 1000000
#define ITERATIONS 500000

main()
{
	int *v;
	int i, n, x = 3;
	clock_t start, end;

	v = (int *) malloc(ARRAY_SIZE * sizeof(int));
	if (v == NULL) {
		fprintf(stderr, "Can't allocate memory for array.\n");
		return -1;
	}
	for (i = 0; i < ARRAY_SIZE; i++)
		v[i] = i;
	start = clock();
	for (i = 0; i < ITERATIONS; i++)
		binsearch(x, v, ARRAY_SIZE);
	end = clock();
	printf("binsearch: %d: %.30f sec\n", binsearch(x, v, ARRAY_SIZE), ((double) (end - start)) / CLOCKS_PER_SEC);
	start = clock();
	for (i = 0; i < ITERATIONS; i++)
		altbinsearch(x, v, ARRAY_SIZE);
	end = clock();
	printf("altbinsearch: %d: %.30f sec\n", binsearch(x, v, ARRAY_SIZE), ((double) (end - start)) / CLOCKS_PER_SEC);
	free(v);

	return 0;
}

/* binsearch:  find x in v[0] <= v[1] <= ... <= v[n - 1] */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low+high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}

	return -1;
}

/* altbinsearch:  find x in v[0] <= v[1] <= ... <= v[n - 1] */
int altbinsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;
	mid = (low + high) / 2;
	while (low <= high && x != v[mid]) {
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid;
		mid = (low + high) / 2;
	}

	return -1;
}
