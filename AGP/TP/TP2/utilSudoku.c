#include <stdlib.h>
#include <stdio.h>
#include <string.h>
         
     
int lireSudoku(FILE *fich,int sudoku[9][9])
{int i,j,res;
 int val; 
 for (i=0; i<9; i++) 
   for (j=0; j<9; j++) 
     {
       res=fscanf(fich, "%d",&val);
       if (res==EOF)
         {
           fprintf(stderr,"Fin de ficher atteinte: manque des coefficients\n");
           exit(-1);
         }
       sudoku[i][j]=val;
     }
 return(0);
}

int ecrireSudoku(FILE *fich,int sudoku[9][9])
{int i,j;
 for (i=0; i<9; i++) 
   {
     for (j=0; j<9; j++) 
       {
         fprintf(fich, "%d ",sudoku[i][j]);
       }
     fprintf(fich, "\n");
   }
 return(0);
}


int sudokuValide (int sudoku[9][9]) {
    int i, j, k, l, r1, r2, value;
    int region[9];
    for (i=0; i<9; i++) {
		for (j=0; j<9; j++) {
		    value=sudoku[i][j];
			 for (k=i+1; k<9; k++) {
				if (sudoku[k][j]==value) {
					return 1;
				}
			}
    		for (k=j+1; k<9; k++) {
				if (sudoku[i][k]==value) {
	   				return 1;
				}
    		}
		}
   	}
	for (r1 = 0; r1 < 9; r1 = r1 + 3) {
		r2=0;
		for (r2 = 0; r2 < 9; r2 = r2 + 3) {
			k=0;
			for (i = r1; i < r1+3; i++) {
				for (j = r2; j < r2+3; j++) {
					region[k]=sudoku[i][j];
					k++;
				}
			}
			for (k=0; k<9; k++) {
				value = region[k];
				for (l = k+1; l < 9; l++) {
					if (region[l] == value) {
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int sudokuSimple(int sudoku[9][9]){
	int w[10];
	int i, j, k, l, m, r1, r2, mainCount=42, count, finalCount=0, value;
	while (mainCount>0 && finalCount<81) { /*while there are stil zeroes*/
		for (i=0; i<9; i++) { /*take each square of the sudoku*/
			for (j=0; j<9; j++) {
				if (sudoku[i][j]==0) { /*if the square is not filled, fill its array of possible solutions with zeroes*/
					for (k=0; k<10; k++) {
						w[k]=0;
					}
					for(l=0; l<9; l++) { /*now add impossible values to this array from every number from the adjacent rows and columns*/
						k=sudoku[i][l];
						w[k]++;
					}
					for(l=0; l<9; l++) { /*now add impossible values to this array from every number from the adjacent rows and columns*/
						k=sudoku[l][j];
						w[k]++;
					}
					r1=((int) i/3)*3;
					r2=((int) j/3)*3;
					for (l=r1;l<r1+3; l++){ /*add impossible values to this array from every number from the adjacent region*/
						for (m=r2; m<r2+3; m++){
							k=sudoku[l][m];
							w[k]++;
						}
					}
					count=0;
					for (k=0; k<10; k++) { /*check if there's more than one possible solution*/
						if (w[k]==0){
							count++;
							value=k;
						}
					}
					if (count==1) { /*if only one solution is possible, change the value of the current square*/
						sudoku[i][j]=value;
					}
				}
			}
		}
		mainCount=0;
		for (i=0; i<9; i++) { /*count the number of empty squares remaining*/
			for (j=0; j<9; j++) {
				if (sudoku[i][j]==0) {
					mainCount++;
				}
			}
		}
		finalCount++;
	}
	return finalCount;
}