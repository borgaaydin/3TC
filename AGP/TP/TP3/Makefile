CFLAGS = -g -Wall -DDEBUG
LDLAGS = -g -Wall -DDEBUG

all: hanoi 

hanoi.o: hanoi.c hanoi.h
	gcc ${CFLAGS} -c hanoi.c  -o hanoi.o

pile.o: pile.c pile.h
	gcc ${CFLAGS} -c pile.c  -o pile.o

main.o:	main.c
	gcc ${CFLAGS} -c main.c -o main.o

hanoi: main.o hanoi.o pile.o
	gcc ${LDFLAGS} main.o hanoi.o pile.o -o hanoi

clean: 
	rm *.o hanoi
