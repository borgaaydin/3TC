#include <stdio.h>
#include <stdlib.h>
#include "access.h"

NODE* newProgram(){
	return NULL;
}

NODE* newNode(char inst[], int nb){
	NODE* node;
	node=(NODE *)malloc(sizeof(NODE));
	node->instruction=inst;
	node->number=nb;
	node->next=NULL;
	return node;
}

NODE* addNode (NODE *program, NODE *added, NODE *previous){
	NODE *temp=previous->next;
	previous->next=added;
	added->next=temp;
	return (program);
}

void printProgram(NODE *program){
	NODE *node=program;
	int i=0;
	while(node!=NULL){
		printf("Node #%d: Instruction=%s; Number=%d", i++, node->instruction, node->number);
	}
}