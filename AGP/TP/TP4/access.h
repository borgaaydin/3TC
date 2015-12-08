#ifndef ACCESS_H
#define ACCESS_H

typedef struct node { //Structure d'un noeud de commande
 char instruction[128];
 int number;
 struct node* subroutine;
 struct node* next;
}NODE;

typedef struct dot {
	double x;
	double y;
	double angle;
}DOT;

static NODE* root;

//initalise a program
NODE* newProgram(NODE *first);

//create a new node with an instruction and a number of repetitions
NODE* newNode(char inst[], int nb, NODE* sub);

//add a node (added) after another node (previous) in a given program (list)
NODE* addNode(NODE *program, NODE *added);

//method to free memory after execution
void memFree(NODE *program);

//display the program
void printProgram(NODE *program);

//method designed to represent a program
void draw(NODE *program);

void generateSVG(NODE* node, FILE* file, DOT* origin);

#endif