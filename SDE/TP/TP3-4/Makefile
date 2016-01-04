CFLAGS = -g -Wall -DDEBUG
LDLAGS = -g -Wall -DDEBUG

all: coordinateur generateur_traffic feux generateur_traffic_prio

generateur_traffic.o: generateur_traffic.c
	gcc ${CFLAGS} -c generateur_traffic.c  -o generateur_traffic.o

generateur_traffic_prio.o: generateur_traffic_prio.c
	gcc ${CFLAGS} -c generateur_traffic_prio.c  -o generateur_traffic_prio.o

coordinateur.o:	coordinateur.c
	gcc ${CFLAGS} -c coordinateur.c -o coordinateur.o

feux.o:	feux.c
	gcc ${CFLAGS} -c feux.c -o feux.o

coordinateur: coordinateur.o
	gcc ${LDFLAGS} coordinateur.o -o Coordinateur

generateur_traffic: generateur_traffic.o
	gcc ${LDFLAGS} generateur_traffic.o -o Generateur_traffic

feux: feux.o
	gcc ${LDFLAGS} feux.o -o Feux

generateur_traffic_prio: generateur_traffic_prio.o
	gcc ${LDFLAGS} generateur_traffic_prio.o -o Generateur_traffic_prio

clean:
	@rm *.o Generateur_traffic Coordinateur Generateur_traffic_prio Feux
