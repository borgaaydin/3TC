#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utilSudoku.h"
	
int main(int argc,char *argv[]) {
	remove("solution");
	FILE *solved = fopen("solution", "a+");
	FILE *fich;
	char *nomFich;
	int sudoku[9][9];

	if (argc!=2) {
		fprintf(stdout," usage: %s nomFich.txt \n",argv[0]);
		exit(-1);
	}
	nomFich=(char *)malloc(100*sizeof(char));
	strcpy(nomFich,argv[1]);
	fich=fopen(nomFich,"r");
 	if (!fich) {
		fprintf(stderr,"erreur d'ouverture du fichier\n");
	}
	lireSudoku(fich,sudoku); /*Display original sudoku*/
	fprintf(stdout,"Read sudoku: \n\n");
	ecrireSudoku(stdout,sudoku);
	printf("\n");

	int i = sudokuSimple(sudoku); /*Solve sudoku*/

	if (sudokuValide(sudoku)==0) {
		ecrireSudoku(solved, sudoku); /*Write solved sudoku to solved*/
		rewind(solved); /*Place cursor back to the beginning of solved*/
		lireSudoku(solved, sudoku);
		printf("%s %d %s\n\n", "The sudoku was solved successfully after", i, "iterations! Here it is: ");
	} else {
		printf("%s\n\n", "An error occured, the sudoku was solved incorrectly...");
	}
	ecrireSudoku(stdout, sudoku); /*Display solved sudoku*/
	printf("\n");

	return(0);
}
