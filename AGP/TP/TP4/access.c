#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "access.h"

NODE* newProgram(NODE *first){
	return first;
}

NODE* newNode(char inst[], NODE *sub, int nb){
	NODE* node;
	node=(NODE *)malloc(sizeof(NODE));
	strcpy(node->instruction, inst);
	node->subroutine=sub;
	node->number=nb;
	node->next=NULL;
	return node;
}

NODE* addNode (NODE *program, NODE *added, NODE *previous){
	added->next=previous->next;
	previous->next=added;
	return (program);
}

void memFree (NODE *program){
	int i=0;
	NODE *tmp;
	while (program != NULL) {
		tmp = program;
		program = program->next;
		if(tmp->subroutine!=NULL){
			subFree(tmp->subroutine);
		}
		free(tmp);
		i++;
	}
	printf("\n%d nodes successfully cleared\n\n", i);
}

void subFree (NODE *sub){
	if(sub->subroutine!=NULL){
		subFree(sub->subroutine);
	}
	free(sub);
}

void printProgram(NODE *program){
	NODE *node=program;
	int i=1;
	while(node!=NULL){
		printf("Node #%d: Instruction=%s; Number=%d", i, node->instruction, node->number);
		if (node->subroutine!=NULL){
			printSub(node->subroutine, 1);
		}
		printf("\n");
		node=node->next;
		i++;
	}
}

void printSub(NODE *sub, int level){
	printf(" & Subroutine level %d: Instruction=%s; Number=%d", level, sub->instruction, sub->number);
	if (sub->subroutine!=NULL){
		level++;
		printSub(sub->subroutine, level);
	}
}