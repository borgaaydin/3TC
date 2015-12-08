%{
#include <stdio.h>
#include "access.h"

void yyerror (char error[]){
	fprintf(stderr,"Fatal error in Logo parsing: %s\n", error);
}

int yywrap(){
	return 1;
}

%} //Règles
%token NUMBER
%token FORWARD
%token REPEAT
%token LEFT
%token RIGHT
	//type de yyval
%union{
	NODE* NODE_TYPE;
	int number;
};
//types
%type <number> NUMBER
%type <NODE_TYPE> INST PROG FILE
%type <NODE_TYPE> FORWARD LEFT RIGHT REPEAT
%%
FILE : PROG
{ 
  root=$1;
}
//programme
PROG : INST 
{
	$$=$1;
}
|PROG INST 
{
	addNode($1,$2);
	$$=$1;
}
//Instructions
INST :
FORWARD NUMBER {
	$$=newNode("FORWARD",$2,NULL);
}
|LEFT NUMBER {
	$$=newNode("LEFT",$2,NULL);
}
|RIGHT NUMBER {
	$$=newNode("RIGHT",$2,NULL);
}
|REPEAT NUMBER '['PROG']'
{
	$$=newNode("REPEAT",$2,$4);
}
%%
int main(){
	remove("drawing.svg");
	yyparse();
	printProgram(root);
	printf("\n");
	draw(root);
	return 0;
}