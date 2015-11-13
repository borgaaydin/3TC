#include <stdio.h>
#include "access.h"

int main(){

	NODE *forward=newNode("FORWARD", 1);
	NODE *right=newNode("RIGHT", 1);
	NODE *left=newNode("LEFT", 1);
	NODE *repeat=newNode("REPEAT", 1);
	printf("New nodes made\n");

	NODE *program=newProgram(forward);
	printf("New program made\n");

	addNode(program, program, right);
	addNode(program, right, left);
	addNode(program, left, repeat);
	printf("Nodes added\n");

	printProgram(program);
}