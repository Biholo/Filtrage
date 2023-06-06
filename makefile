CC=gcc
CFLAGS=-Wall -g -std=c17 -pedantic 

all: ABR_test Filtrage

ABR.o: ABR.c ABR.h
	$(CC) -c ABR.c $(FLAGS)

ABR_test: ABR_test.c ABR.h
	$(CC) ABR_test.c -o ABR_test $(FLAGS)

Filtrage: filtrage.c ABR.o
	$(CC) filtrage.c -o Filtrage ABR.o$(FLAGS) -g

clean:
	rm -f *.o *.pdf *.dot Filtrage