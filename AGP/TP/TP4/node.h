#ifndef NODE_H
#define NODE_H

struct model_node {
	char[] instruction;
	int number;
	struct model_node *next;
}

typedef struct model_node NODE;

#endif NODE_H