#include <stdio.h>

#define PAGE_LENGTH 25
#define HEADER_LENGTH 2
#define FOOTER_LENGTH 1

int print(char *filename);

main(int argc, char *argv[])
{
	int i;

	for (i = 1; i < argc; i++) {
		if (print(argv[i]) == 0) {
			fprintf(stderr, "Error printing %s\n", argv[i]);
			return 1;
		}
	}

	return 0;
}

#define MAXLINE 1000

int print(char *filename)
{
	FILE *fp;
	char line[MAXLINE];
	int row;
	long page_number;

	fp = fopen(filename, "r");
	if (fp == NULL)
		return 0;
	page_number = 1;
	while (!feof(fp)) {
		printf("=== %s page %ld\n", filename, page_number);
		printf("\n");
		for (row = HEADER_LENGTH; row < PAGE_LENGTH - FOOTER_LENGTH; row++) {
			if (fgets(line, MAXLINE, fp) == NULL)
				printf("\n");
			else
				printf("%s", line);
		}
		printf("\n");
		page_number++;
	}
	fclose(fp);

	return page_number;
}
