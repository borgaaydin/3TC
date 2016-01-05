#ifndef UTIL_H
#define UTIL_H

struct fifo {
	int src;
	int dest;
	int id;
	struct fifo* next;
};

typedef struct fifo FIFO;

struct message {
	long type;
	FIFO* car;
};

typedef struct message MSG;

#endif
