PROGRAMS = calc

CC = gcc
CFLAGS = -g

all: $(PROGRAMS)

calc: main.o getop-4-11.o stack.o getch.o
	$(CC) -o calc main.o getop-4-11.o stack.o getch.o

main.o: main.c calc.h

getop.o: getop.c calc.h

stack.o: stack.c calc.h

getch.o: getch.c calc.h

getop-4-11.o: getop-4-11.c calc.h

clean:
	rm -f $(PROGRAMS) *.o

.PHONY: all clean
