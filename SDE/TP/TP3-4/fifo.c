#include <stdio.h>
#include "fifo.h"

FIFO* init(){
	FIFO* ret=(FIFO*)(malloc(sizeof(FIFO)));
	return ret;
}

void add(FIFO* root, int src, int dest, int id){
	FIFO* ret=(FIFO*)(malloc(sizeof(FIFO)));
	ret->src=src;
	ret->dest=dest;
	ret->id=id;
	ret->next=NULL;
	if(root==NULL){
		root=ret;
	}
	else while(root->next!=NULL){
		root=root->next;
	}
	root->next=ret;
}
