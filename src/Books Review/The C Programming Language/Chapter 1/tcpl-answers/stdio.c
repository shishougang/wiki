#include <fcntl.h>
#include <unistd.h>
#include "stdio.h"
#define PERMS 0666	/* RW for owner, group, others */

FILE _iob[OPEN_MAX] = {	/* stdin, stdout, stderr: */
	{ 0, (char *) 0, (char *) 0, _READ, 0 },
	{ 0, (char *) 0, (char *) 0, _WRITE, 1 },
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

/* fopen:  open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;	/* found free slot */
	if (fp >= _iob + OPEN_MAX)	/* no free slots */
		return NULL;

	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)	/* couldn't access name */
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

int fclose(FILE *fp)
{
	int status = 0;

	if (fflush(fp) == EOF)
		status = EOF;
	free(fp->base);
	fp->flag &= ~(_READ | _WRITE);
	if (close(fp->fd) != 0)
		status = EOF;

	return status;
}

int fflush(FILE *fp)
{
	int i, bufsize;

	if (fp == NULL) {
		for (i = 0; i < OPEN_MAX; i++) {
			if (_iob[i].flag & _WRITE) {
				if (fflush(&_iob[i]) == EOF)
					return EOF;
			}
		}
	} else {
		if (!(fp->flag & _WRITE))
			return EOF;
		/* We can't just call _flushbuf because we don't have a
		   character to pass to it. */
		bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
		fp->ptr = fp->base;
		fp->cnt += write(fp->fd, fp->ptr, bufsize - fp->cnt);
		if (fp->cnt != bufsize) {
			fp->flag |= _ERR;
			return EOF;
		}
	}

	return 0;
}

int fseek(FILE *fp, long offset, int origin)
{
	/* In this library reading and writing are mutually exclusive. */
	if (fp->flag & _WRITE) {
		if (fflush(fp) != 0)
			return -1;
	} else if (fp->flag & _READ) {
		/* Refill the input buffer at the next opportunity. */
		fp->cnt = 0;
	}
	if (lseek(fp->fd, offset, origin) == -1)
		return -1;
	fp->flag &= ~(_EOF | _ERR);

	return 0;
}

/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
	int bufsize;

	if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL)	/* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;		/* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

/* _flushbuf:  empty buffer to fp */
int _flushbuf(int c, FILE *fp)
{
	int bufsize;

	if ((fp->flag&(_WRITE|_EOF|_ERR)) != _WRITE)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL) {	/* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;		/* can't get buffer */
		fp->cnt = bufsize;
	}
	fp->ptr = fp->base;
	fp->cnt += write(fp->fd, fp->ptr, bufsize - fp->cnt);
	if (fp->cnt != bufsize) {
		fp->flag |= _ERR;
		return EOF;
	}
	fp->cnt--;
	*fp->ptr++ = c;
	return c;
}
