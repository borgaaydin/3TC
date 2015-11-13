#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "access.h"

NODE* newProgram(NODE *first){
	return first;
}

NODE* newNode(char inst[], int nb){
	NODE* node;
	node=(NODE *)malloc(sizeof(NODE));
	strcpy(node->instruction, inst);
	node->number=nb;
	node->next=NULL;
	return node;
}

NODE* addNode (NODE *program, NODE *added, NODE *previous){
	added->next=previous->next;
	previous->next=added;
	return (program);
}

void printProgram(NODE *program){
	NODE *node=program;
	int i=1;
	while(node!=NULL){
		printf("Node #%d: Instruction=%s; Number=%d\n", i, node->instruction, node->number);
		node=node->next;
		i++;
	}
}