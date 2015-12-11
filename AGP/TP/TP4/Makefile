CFLAGS = -g -Wall -DDEBUG
LDLAGS = -g -Wall -DDEBUG

all: logo

logo.tab.c: logo.y
	bison -d logo.y

lex.yy.c: logo.l
	flex logo.l

logo: logo.tab.c lex.yy.c access.c
	gcc ${LDFLAGS} logo.tab.c lex.yy.c access.c -lm -o main

simple: main.c access.c
	gcc ${LDFLAGS} main.c access.c -o main

test:
	./main<test.logo

koch:
	./main<koch.logo

val:
	valgrind --leak-check=yes ./main<koch.logo

clean:
	\rm -rf *.o main logo.tab.* lex.yy.c main.dSYM *.svg
