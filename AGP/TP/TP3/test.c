#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

int main() {
  
  PILE pile1,pile2;
  int i,elem,k;
 
  pile1 = InitPile();
  pile2 = InitPile();
 
  //testing 2 empty piles
  fprintf(stdout, "Test 1 : Testing 2 empty piles --- --- \n");
  afficherPile(pile1);
  afficherPile(pile2);
  fprintf(stdout, "Finished Test 1 --- --- \n");
   
  //testing stacking a pile with 10 values
  fprintf(stdout, "Test 2 : Testing a pile stacking with 10 values --- --- \n");
  for (i=0;i<10;i++){
      elem = i;
      Empiler(&pile1, elem);
  }
  afficherPile(pile1);
  afficherPile(pile2);
  fprintf(stdout, "Finished Test 2 --- --- \n");
  
  //testing destack of a pile
  fprintf(stdout, "Test 3 : Testing a destack --- --- \n");
  ELEMPILE *visitor1;
  visitor1=pile1;

  while((*pile1).suivant != NULL){
    Depiler(&pile1);
    afficherPile(pile1);
  }
  fprintf(stdout, "Pile is empty !\n");
  fprintf(stdout, "Finished Test 3 --- --- \n");
}

