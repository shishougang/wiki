all: bloom

bloom: bloom.o test.o
	gcc -o bloom -Wall -pedantic bloom.o test.o

bloom.o: bloom.c bloom.h
	gcc -o bloom.o -Wall -pedantic -ansi -c bloom.c
test.o: test.c bloom.h
	gcc -o test.o -Wall -pedantic -ansi -c test.c
