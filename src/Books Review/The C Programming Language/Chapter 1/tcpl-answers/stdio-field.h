/* This is the example <stdio.h> from page 176 in section 8.5. */

#define NULL	0
#define EOF	(-1)
#define BUFSIZ	1024
#define OPEN_MAX	20	/* max #files open at once */

typedef struct _iobuf {
	int cnt;	/* characters left */
	char *ptr;	/* next character position */
	char *base;	/* location of buffer */
	unsigned int read : 1;
	unsigned int write : 1;
	unsigned int unbuf : 1;
	unsigned int eof : 1;
	unsigned int err : 1;
	int fd;	/* file descriptor */
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin	(&_iob[0])
#define stdout	(&_iob[1])
#define stderr	(&_iob[2])

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)		(((p)->eof) != 0)
#define ferror(p)	(((p)->err) != 0)
#define fileno(p)	((p)->fd);

#define getc(p)		(--(p)->cnt >= 0 \
			? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)	(--(p)->cnt >= 0 \
			? *(p)->ptr++ = (x) : _flushbuf((x,p))

#define getchar()	getc(stdin)
#define putchar(x)	putc((x), stdout)
