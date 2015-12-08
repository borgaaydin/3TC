#include <stdio.h>
#include <stdlib.h>
#include "access.h"

int main(){

	NODE *forward=newNode("FORWARD", 1, NULL);
	NODE *right=newNode("RIGHT", 1, NULL);
	NODE *left=newNode("LEFT", 1, NULL);
	NODE *repeat=newNode("REPEAT", 1, newNode("REPEAT", 1, newNode("FORWARD", 1, NULL)));
	printf("\nNew nodes made\n");

	NODE *program=newProgram(forward);
	printf("New program made\n");

	addNode(program, right);
	addNode(program, left);
	addNode(program, repeat);
	printf("Nodes added\n\n");

	printProgram(program);

	//draw(program);

	memFree(program);
}