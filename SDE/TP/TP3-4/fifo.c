#include <stdio.h>
#include "fifo.h"

FIFO* newNode(int src, int dest, int id){
	FIFO* ret=(FIFO*)(malloc(sizeof(FIFO)));
	ret->src=src;
	ret->dest=dest;
	ret->id=id;
	ret->next=NULL;
	return (ret);
}

FIFO* addNode(FIFO* root, FIFO* next){
	if (root->next!=NULL){
		root->next=addNode(root->next,next);
	}
	else {
		root->next=next;
	}
	return (root);
}
