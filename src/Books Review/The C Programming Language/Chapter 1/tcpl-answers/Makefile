PROGRAMS = 80long copy catblank catescape celsius charfreq countbtn countchars \
	countdso countlines eof fahr fahrfunc getchar hello longest power \
	printlines wc wordlength stripline reverse longest-extern detab entab fold \
	typerange htoi squeeze any bitwise binsearch escape expand itoa strindex \
	atof calc printd qsort itoa-recursive reverse-recursive getint strn sort \
	echo find expr entab-cmd detab-cmd tail sort-ptr sort-field dcl undcl \
	keytab countwords c-vars crossref wordfreq simple-cpp uncomment case utol \
	ltou quoted-printable minprintf minscanf calc-scanf cat simple-diff \
	find-cmd print isupper syntax copy-sys cp cat-sys stdio.o fseek-test \
	stdio-field.o test-fields-f test-fields-b fsize malloc-test

CC = gcc
CFLAGS = -g

all: $(PROGRAMS)

atof: LDFLAGS += -lm

calc: LDFLAGS += -lm

simple-cpp: lookup.o

utol: case
	ln -sf case utol

ltou: case
	ln -sf case ltou

stdio.o: stdio.h

stdio-field.o: stdio-field.h

test-fields-f: test-fields.c stdio.o
	$(CC) -o $@ -I. $(CFLAGS) -UBITFIELDS $^

test-fields-b: test-fields.c stdio-field.o
	$(CC) -o $@ -I. $(CFLAGS) -DBITFIELDS $^

malloc-test: malloc.o

clean:
	rm -f $(PROGRAMS) *.o fseek-test.out

.PHONY: all clean
