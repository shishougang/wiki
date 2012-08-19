#include <stdio.h>
#include <string.h>
#define MAXLINE 1000
#define MAXFILES 10

long find(FILE *fp, char *filename, char *pattern, int number, int except);
int getline(FILE *fp, char s[], int lim);

/* find:  print lines that match pattern from 1st arg */
main(int argc, char *argv[])
{
	FILE *fp;
	char *pattern;
	char *files[MAXFILES];
	int num_files = 0;
	int c, i, except = 0, number = 0, found = 0;

	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				printf("find: illegal option %c\n", c);
				argc = 0;
				found = -1;
				break;
			}
	if (argc < 1) {
		printf("Usage: find -x -n pattern\n");
		return -1;
	}
	pattern = *argv;
	while (--argc > 0 && num_files < MAXFILES) {
		argv++;
		files[num_files++] = *argv;
	}
	if (num_files == 0) {
		found += find(stdin, NULL, pattern, number, except);
	} else {
		for (i = 0; i < num_files; i++) {
			fp = fopen(files[i], "r");
			if (fp == NULL) {
				fprintf(stderr, "Can't open %s\n", files[i]);
				return -1;
			}
			if (num_files == 1)
				find(fp, NULL, pattern, number, except);
			else
				find(fp, files[i], pattern, number, except);
			fclose(fp);
		}
	}
	return found;
}

long find(FILE *fp, char *filename, char *pattern, int number, int except)
{
	long lineno = 0;
	int found = 0;
	char line[MAXLINE];

	while (getline(fp, line, MAXLINE) > 0) {
		lineno++;
		if ((strstr(line, pattern) != NULL) != except) {
			if (filename != NULL)
				printf("%s:", filename);
			if (number)
				printf("%ld:", lineno);
			printf("%s", line);
			found++;
		}
	}

	return found;
}

/* getline:  read a line into s, return length */
int getline(FILE *fp, char s[], int lim)
{
	int c, i;

	for (i=0; i<lim-1 && (c=getc(fp))!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	for ( ; c != EOF && c != '\n'; ++i)
		c = getc(fp);
	return i;
}
