#ifndef ACCESS_H
#define ACCESS_H

#include "node.h"

//initalise a program
NODE* newProgram(NODE *first);

//create a new node with an instruction and a number of repetitions
NODE* newNode(char inst[], NODE *sub, int nb);

//add a node (added) after another node (previous) in a given program (list)
NODE* addNode(NODE *program, NODE *added, NODE *previous);

//method to free memory after execution
void memFree(NODE *program);

void subFree(NODE *sub);

//display the program
void printProgram(NODE *program);

//method designed to handle subroutine printing
void printSub(NODE *sub, int level);

#endif