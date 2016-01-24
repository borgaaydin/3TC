CFLAGS = -g -Wall -DDEBUG
LDLAGS = -g -Wall -DDEBUG

all: coordinateur generateur_traffic feux generateur_traffic_prioritaire

generateur_traffic.o: generateur_traffic.c
	gcc ${CFLAGS} -c generateur_traffic.c  -o generateur_traffic.o

generateur_traffic_prioritaire.o: generateur_traffic_prioritaire.c
	gcc ${CFLAGS} -c generateur_traffic_prioritaire.c  -o generateur_traffic_prioritaire.o

coordinateur.o:	coordinateur.c
	gcc ${CFLAGS} -c coordinateur.c -o coordinateur.o

feux.o:	feux.c
	gcc ${CFLAGS} -c feux.c -o feux.o

fifo.o:	fifo.c
	gcc ${CFLAGS} -c fifo.c -o fifo.o

coordinateur: coordinateur.o fifo.o
	gcc ${LDFLAGS} coordinateur.o fifo.o -o Coordinateur

generateur_traffic: generateur_traffic.o
	gcc ${LDFLAGS} generateur_traffic.o -o Generateur_traffic

feux: feux.o
	gcc ${LDFLAGS} feux.o -o Feux

generateur_traffic_prioritaire: generateur_traffic_prioritaire.o
	gcc ${LDFLAGS} generateur_traffic_prioritaire.o -o Generateur_traffic_priotaire

clean:
	@rm *.o Generateur_traffic Coordinateur Generateur_traffic_priotaire Feux
	./clean.sh
