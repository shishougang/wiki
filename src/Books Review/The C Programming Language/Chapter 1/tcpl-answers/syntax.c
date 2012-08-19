#include <stdio.h>
#include <string.h>

static int stack_size(void);
static int push(int item);
static int pop(void);
static int peek(void);

static int getch(void);
static char *last_read(char *buf, int num);

main(int argc, char *argv[])
{
	int c, num_errors;
	unsigned long int line_num, temp_line_num;
	char buf[3]; /* Big enough for comment delimiters plus '\0'. */

	line_num = 1;
	num_errors = 0;
	while ((c = getch()) != EOF) {
		if (strcmp(last_read(buf, sizeof(buf) - 1), "/*") == 0) {
			temp_line_num = line_num;
			while ((c = getch()) != EOF) {
				if (strcmp(last_read(buf, sizeof(buf) - 1), "*/") == 0)
					break;
			}
			if (c == EOF) {
				printf("%lu: Unterminated comment.\n", temp_line_num);
				num_errors++;
			}
			continue;
		}
		switch (c) {
			case '(':
			case '[':
			case '{':
				if (push(c) == -1) {
					fprintf(stderr, "Out of memory.\n");
					return 2;
				}
				break;
			case ')':
				if (peek() == '(') {
					pop();
				} else {
					printf("%lu: Unmatched '%c'.\n", line_num, c);
					num_errors++;
				}
				break;
			case ']':
				if (peek() == '[') {
					pop();
				} else {
					printf("%lu: Unmatched '%c'.\n", line_num, c);
					num_errors++;
				}
				break;
			case '}':
				if (peek() == '{') {
					pop();
				} else {
					printf("%lu: Unmatched '%c'.\n", line_num, c);
					num_errors++;
				}
				break;
			case '"':
				temp_line_num = line_num;
				while ((c = getch()) != EOF) {
					if (c == '\\')
						getch();
					else if (c == '\n')
						line_num++;
					else if (c == '"')
						break;
				}
				if (c == EOF) {
					printf("%lu: Unterminated string literal.\n", temp_line_num);
					num_errors++;
				}
				break;
			case '\'':
				temp_line_num = line_num;
				while ((c = getch()) != EOF) {
					if (c == '\\')
						getch();
					else if (c == '\n')
						line_num++;
					else if (c == '\'')
						break;
				}
				if (c == EOF) {
					printf("%lu: Unterminated character constant.\n", temp_line_num);
					num_errors++;
				}
				break;
			case '\n':
				line_num++;
				break;
		}
	}
	while (stack_size() > 0) {
		printf("%lu: Unmatched '%c'.\n", line_num, pop());
		num_errors++;
	}
	if (num_errors > 0) {
		printf("%d errors found.\n", num_errors);
		return 1;
	}

	return 0;
}

#define MAXSTACK 100

static int stack[MAXSTACK];
static int *stackp = stack;

static int stack_size(void)
{
	return stackp - stack;
}

static int push(int item)
{
	if (stackp - stack >= MAXSTACK)
		return -1;
	*(stackp++) = item;

	return item;
}

static int pop(void)
{
	if (stackp - stack < 1)
		return -1;

	return *(--stackp);
}

static int peek(void)
{
	if (stackp - stack < 1)
		return -1;

	return *(stackp - 1);
}

#define MAXBUFFER 100
static int buffer[MAXBUFFER];
static int bufferi = 0;

static int getch(void)
{
	int c;

	c = getchar();
	if (c != EOF) {
		buffer[bufferi] = c;
		bufferi = (bufferi + 1) % MAXBUFFER;
	}

	return c;
}

static char *last_read(char *buf, int num)
{
	int i, bi;

	if (num > MAXBUFFER)
		num = MAXBUFFER;
	bi = bufferi - num;
	if (bi < 0)
		bi += MAXBUFFER;
	for (i = 0; i < num; i++) {
		buf[i] = buffer[bi];
		bi = (bi + 1) % MAXBUFFER;
	}
	buf[i] = '\0';

	return buf;
}
