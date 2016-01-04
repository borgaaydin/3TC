#ifndef FIFO_H
#define FIFO_H

struct fifo {
	int src;
	int dest;
	int id;
	struct fifo* next;
};

typedef struct fifo FIFO;

FIFO* init();

void add(FIFO* root, int src, int dest, int id);

#endif
