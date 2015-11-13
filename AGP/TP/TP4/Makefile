CFLAGS = -g -Wall -DDEBUG
LDLAGS = -g -Wall -DDEBUG

all: main 

access.o: access.c access.h
	gcc ${CFLAGS} -c access.c  -o access.o

main.o:	main.c
	gcc ${CFLAGS} -c main.c -o main.o

main: main.o access.o
	gcc ${LDFLAGS} main.o access.o -o main

clean: 
	\rm -rf *.o main
