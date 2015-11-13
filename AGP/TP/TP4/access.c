#include <stdio.h>
#include "access.h"

NODE* newProgram(){
	return NULL;
}

NODE* newNode(char[] inst, int nb){
	NODE* node;
	node=(NODE *)malloc(sizeof(NODE));
	node->instruction=inst;
	node->number=nb;
	node->next=NULL;
	return newNode;
}

NODE* addNode (LIST list, NODE *added, NODE *previous){
	NODE *temp=previous->next;
	previous->next=added;
	added->next=temp;
	return (list);
}

void printProgram(LIST program)