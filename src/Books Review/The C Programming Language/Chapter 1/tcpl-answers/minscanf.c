#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

#define ungetchar(c) ungetc((c), stdin)

int minscanf(char *format, ...);

main()
{
	int d;
	char s[100];
	float f;

	printf("%%d %%s %%f\n", &d, s, &f);
	minscanf("%d %s %f", &d, s, &f);
	printf("%d %s %f\n", d, s, f);

	return 0;
}

int minscanf(char *format, ...)
{
	union {
		int *d;
		char *s;
		float *f;
		short int *hd;
		long int *ld;
		double *lf;
		long double *Lf;
	} val;
	va_list ap;
	char *fp;
	int c;
	int num = 0;

	va_start(ap, format);
	fp = format;
	while (*fp != '\0') {
		while (*fp == ' ' || *fp == '\t')
			fp++;
		if (*fp == '%') {
			*fp++;
			if (*fp == 'h') {
				fp++;
				if (*fp == 'd') {
					val.hd = va_arg(ap, short int *);
					if (scanf("%hd", val.hd) != 1)
						break;
					num++;
				} else {
					break;
				}
			} else if (*fp == 'l') {
				if (*fp == 'd') {
					val.ld = va_arg(ap, long int *);
					if (scanf("%ld", val.ld) != 1)
						break;
					num++;
				}
				if (*fp == 'f') {
					val.lf = va_arg(ap, double *);
					if (scanf("%lf", val.lf) != 1)
						break;
					num++;
				} else {
					break;
				}
			} else if (*fp == 'L') {
				if (*fp == 'f') {
					val.Lf = va_arg(ap, long double *);
					if (scanf("%Lf", val.Lf) != 1)
						break;
					num++;
				} else {
					break;
				}
			} else if (*fp == 'd') {
				val.d = va_arg(ap, int *);
				if (scanf("%d", val.d) != 1)
					break;
				num++;
			} else if (*fp == 'c') {
				val.s = va_arg(ap, char *);
				if (scanf("%c", val.s) != 1)
					break;
				num++;
			} else if (*fp == 's') {
				val.s = va_arg(ap, char *);
				if (scanf("%s", val.s) != 1)
					break;
				num++;
			} else if (*fp == 'f') {
				val.f = va_arg(ap, float *);
				if (scanf("%f", val.f) != 1)
					break;
				num++;
			} else if (*fp == '%') {
				while ((c = getchar()) == ' ' || c == '\t')
					;
				if (c != '%') {
					ungetchar(c);
					break;
				}
			} else {
				break;
			}
		} else {
			while ((c = getchar()) == ' ' || c == '\t')
				;
			if (*fp != c) {
				ungetchar(c);
				break;
			}
		}
		fp++;
	}
	va_end(ap);

	return num;
}
