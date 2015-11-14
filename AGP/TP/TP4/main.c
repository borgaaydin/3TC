#include <stdio.h>
#include <stdlib.h>
#include "access.h"

int main(){

	NODE *forward=newNode("FORWARD", NULL, 1);
	NODE *right=newNode("RIGHT", NULL, 1);
	NODE *left=newNode("LEFT", NULL, 1);
	NODE *repeat=newNode("REPEAT", newNode("REPEAT", newNode("FORWARD", NULL, 1), 1), 1);
	printf("\nNew nodes made\n");

	NODE *program=newProgram(forward);
	printf("New program made\n");

	addNode(program, right, program);
	addNode(program, left, right);
	addNode(program, repeat, left);
	printf("Nodes added\n\n");

	printProgram(program);

	memFree(program);
}