#ifndef ACCESS_H
#define ACCESS_H

#include "node.h"

//initalise a program
NODE* newProgram(NODE *first);

//create a new node with an instruction and a number of repetitions
NODE* newNode(char inst[], int nb);

//add a node (added) after another node (previous) in a given program (list)
NODE* addNode(NODE *program, NODE *added, NODE *previous);

//display the program
void printProgram(NODE *program);

#endif