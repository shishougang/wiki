#include <stdio.h>
#include <fcntl.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1

/* cat:  concatenate files */
main(int argc, char *argv[])
{
	int fd;
	void filecopy(int, int);
	char *prog = argv[0];	/* program name for errors */

	if (argc == 1)	/* no args; copy standard input */
		filecopy(STDIN_FILENO, STDOUT_FILENO);
	else
		while (--argc > 0)
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
				fprintf(stderr, "%s: can't open %s\n",
					prog, *argv);
				exit(1);
			} else {
				filecopy(fd, STDOUT_FILENO);
				close(fd);
			}
	return 0;
}

/* filecopy:  copy file ifd to file ofd */
void filecopy(int ifd, int ofd)
{
	char c;

	while (read(ifd, &c, sizeof(c)) == 1)
		write(ofd, &c, 1);
}
