#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "access.h"
#define PI 3.141592653589793

NODE* newProgram(NODE *first){
	return first;
}

NODE* newNode(char inst[], int nb, NODE *sub){
	NODE* node;
	node=(NODE *)malloc(sizeof(NODE));
	strcpy(node->instruction, inst);
	node->subroutine=sub;
	node->number=nb;
	node->next=NULL;
	return node;
}

NODE* addNode (NODE *program, NODE *added){	
	if (program->next!=NULL){
		program->next=addNode(program->next,added);
	}
	else {
		program->next=added;
	}
	return (program);
}

void memFree (NODE *program){
	int i=0;
	NODE *tmp;
	while (program != NULL) {
		tmp = program;
		program = program->next;
		if(tmp->subroutine!=NULL){
			memFree(tmp->subroutine);
		}
		free(tmp);
		i++;
	}
	printf("\n%d nodes successfully cleared\n\n", i);
}

void printProgram(NODE *program){
	NODE *node=program;
	while(node!=NULL){
		printf("[%s %d", node->instruction, node->number);
		if (node->subroutine!=NULL){
			printProgram(node->subroutine);
		}
		printf("]");
		node=node->next;
	}
}

void generateSVG(NODE* node, FILE* drawing, DOT* origin){
	NODE* current=node;
	while(current!=NULL){
		printf("Node analysed: %s, %d, %s\n", current->instruction, current->number, current->subroutine->instruction);
		if(strcmp(current->instruction,"FORWARD")==0){
			printf("Forward %d\n", current->number);
			fprintf(drawing,"<line x1=\"%.3f\" y1=\"%.3f\"",origin->x,origin->y);
			origin->x = origin->x + current->number*cos(origin->angle);
			origin->y = origin->y + current->number*sin(origin->angle);
			fprintf(drawing," x2=\"%.3f\" y2=\"%.3f\" stroke=\"red\" />\n",origin->x,origin->y);
		}
		if(strcmp(current->instruction,"RIGHT")==0){
			printf("Right %d\n", current->number);
			origin->angle+=(current->number)*PI/180;
		}
		if(strcmp(current->instruction,"LEFT")==0){
			printf("Left %d\n", current->number);
			origin->angle-=(current->number)*PI/180;
		}
		if(strcmp(current->instruction,"REPEAT")==0){
			int i;
			printf("Repeating %s %d times...\n", current->subroutine->instruction, current->number);
			for(i=0; i<current->number; i++){
				generateSVG(current->subroutine, drawing, origin);
			}
			printf("Out of repeat\n");
		}
		current=current->next;
	}
}

void draw(NODE *program){
	FILE* drawing=fopen("drawing.svg", "aw+");
	DOT* origin=(DOT*) malloc(sizeof(DOT));
	origin->x=250;
	origin->y=250;
	origin->angle=0;

	fprintf(drawing,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"500\" height=\"500\">\n");
	generateSVG(program, drawing, origin);
	fprintf(drawing,"</svg>");

	memFree(program);
	free(origin);
}






