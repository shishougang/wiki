#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void minprintf(char *fmt, ...);

main()
{
	minprintf("%% %d %f %s\n", 10, 3.14, "string");
	printf("%% %d %f %s\n", 10, 3.14, "string");
	minprintf("%% %10d %3f %7s %p\n", 10, 3.14, "string", NULL);
	printf("%% %10d %3f %7s %p\n", 10, 3.14, "string", NULL);

	return 0;
}

enum { ALIGN_LEFT, ALIGN_RIGHT };

/* minprintf:  minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
	va_list ap;	/* points to each unnamed arg in turn */
	char *p, *sval;
	int ival;
	double dval;
	void *pval;
	int alignment = ALIGN_RIGHT;
	int width;
	int precision = 0;
	int i;

	va_start(ap, fmt); /* make ap point to 1st unnamed arg */
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		p++;
		if (*p == '-') {
			alignment = ALIGN_LEFT;
			p++;
		}
		width = 0;
		while (isdigit(*p)) {
			width = width * 10 + (*p - '0');
			p++;
		}
		switch(*p) {
		case 'd':
			ival = va_arg(ap, int);
			if (alignment == ALIGN_RIGHT)
				printf("%*d", width, ival);
			else
				printf("%-*d", width, ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			if (alignment == ALIGN_RIGHT)
				printf("%*f", width, dval);
			else
				printf("%-*f", width, dval);
			break;
		case 's':
			sval = va_arg(ap, char *);
			if (alignment == ALIGN_RIGHT) {
				for (i = 0; i < width - (int) strlen(sval); i++)
					putchar(' ');
			}
			for (i = 0; sval[i] != '\0'; i++)
				putchar(sval[i]);
			if (alignment == ALIGN_LEFT) {
				for ( ; i < width; i++)
					putchar(' ');
			}
			break;
		case 'p':
			pval = va_arg(ap, void *);
			if (alignment == ALIGN_RIGHT)
				printf("%*p", width, pval);
			else
				printf("%-*p", width, pval);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap);	/* clean up when done */
}
