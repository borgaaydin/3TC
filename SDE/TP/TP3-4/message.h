#ifndef MESSAGE_H
#define MESSAGE_H

struct message {
	long type;
	int src;
	int dest;
	int id;
};

typedef struct message MSG;

#endif
