#include <ctype.h>
#include <stdio.h>

unsigned hash(char *s);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void undef(char *);

struct nlist {		/* table entry: */
	struct nlist *next;	/* next entry in chain */
	char *name;			/* defined name */
	char *defn;			/* replacement text */
};

#define MAXLINE 1000
#define MAXTOKEN 100

int getline(char *line, int lim);
int gettoken(char *line, char *token, char **start, char **end);
void print_substring(char *start, char *end);

main()
{
	char line[MAXLINE];
	char token[MAXTOKEN], *replacement;
	char *start, *end, *prev_end;
	struct nlist *np;
	int i;

	while (getline(line, MAXLINE) > 0) {
		if (line[0] == '#') {
			gettoken(line + 1, token, &start, &end);
			if (strcmp(token, "define") == 0) {
				gettoken(end, token, &start, &end);
				replacement = end;
				while (isspace(*replacement))
					replacement++;
				/* remove trailing white space */
				for (i = strlen(replacement) - 1;
				     i > 0 && isspace(replacement[i]); i--)
					replacement[i] = '\0';
				install(token, replacement);
			} else if (strcmp(token, "undef") == 0) {
				gettoken(end, token, &start, &end);
				undef(token);
			}
		} else {
			end = line;
			prev_end = end;
			while (gettoken(end, token, &start, &end) > 0) {
				print_substring(prev_end, start);
				np = lookup(token);
				if (np == NULL)
					printf("%s", token);
				else
					printf("%s", np->defn);
				prev_end = end;
			}
			printf("%s", end);
		}
	}

	return 0;
}

int getline(char *line, int lim)
{
	int c, i;

	i = 0;
	while (i < lim - 1 && c != '\n') {
		c = getchar();
		if (c == EOF)
			break;
		line[i++] = c;
		lim--;
	}
	line[i] = '\0';

	return i;
}

int gettoken(char *line, char *token, char **start, char **end)
{
	while (isspace(*line))
		line++;
	if (*line == '\0') {
		*token = '\0';
		return 0;
	}
	*start = line;
	if (isalpha(*line) || *line == '_') {
		while (isalpha(*line) || isdigit(*line) || *line == '_')
			*token++ = *line++;
	} else {
		*token++ = *line++;
	}
	*token = '\0';
	*end = line;

	return *end - *start;
}

void print_substring(char *start, char *end)
{
	while (start < end) {
		putchar(*start);
		start++;
	}
}
