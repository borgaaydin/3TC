#ifndef NODE_H
#define NODE_H

struct model_node {
	char instruction[128];
	int number;
	struct model_node *next;
};

typedef struct model_node NODE;

#endif