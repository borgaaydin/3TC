#include <stdio.h>
#include <stdlib.h>
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
	if(root==NULL){
		return(next);
	}
	while(root->next!=NULL){
		root=root->next;
	}
	root->next=next;
	return root;
}

FIFO* delNode(FIFO* root){
	FIFO* temp=(FIFO*)malloc(sizeof(FIFO));
	if(root==NULL){
		temp=NULL;
	}
	else{
		temp=root->next;
		free(root);
	}
	return temp;
}

FIFO* emptyFIFO(FIFO* root){
	FIFO* temp;
	while(temp!=NULL){
		temp=delNode(root);
	}
	return(temp);
}
