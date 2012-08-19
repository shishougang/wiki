#include <stdio.h>

#define INPUT_FILENAME "fseek-test.in"
#define OUTPUT_FILENAME "fseek-test.out"

main()
{
	FILE *fp;

	printf("fp = fopen(\"%s\", \"r\")\n", INPUT_FILENAME);
	fp = fopen(INPUT_FILENAME, "r");
	if (fp == NULL) {
		fprintf(stderr, "Can't open `%s'.\n", INPUT_FILENAME);
		return 1;
	}
	printf("getc(fp) -> %c\n", getc(fp));
	printf("getc(fp) -> %c\n", getc(fp));
	printf("fseek(fp, 13, 0)\n");
	fseek(fp, 13, 0);
	printf("getc(fp) -> %c\n", getc(fp));
	printf("fclose(fp)\n");
	fclose(fp);
	printf("fp = fopen(\"%s\", \"r\")\n", OUTPUT_FILENAME);
	fp = fopen(OUTPUT_FILENAME, "w");
	printf("putc('a', fp)\n");
	putc('a', fp);
	printf("putc('b', fp)\n");
	putc('b', fp);
	printf("putc('c', fp)\n");
	putc('c', fp);
	printf("putc('d', fp)\n");
	putc('d', fp);
	printf("fseek(fp, -3L, 2)\n");
	fseek(fp, -3L, 2);
	printf("putc('x', fp)\n");
	putc('x', fp);
	printf("putc('y', fp)\n");
	putc('y', fp);
	/* Should produce "axyd". */
	printf("fclose(fp)\n");
	fclose(fp);

	return 0;
}
