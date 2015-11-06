#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
#include "pile_type.h"

int error1(char *message){
	fprintf(stderr, "Error : %s\n", message);
	exit(-1);
}

/************************************************
* \brief  initialise une pile
**************************************************/    
PILE InitPile(){
	return NULL;
}

/************************************************
* \brief     ajoute l'élément elem au sommet de la pile pointée par ppile
* \param ppile un pointeur vers la pile 
* \param elem L'élément à rajouter au sommet de pile
* \pre Precondition: ppile pointe sur une pile valide
* \post Postcondition: La pile pointée par ppile a été modifiée:
          un élément de valeur elem a été rajouté au sommet de pile. 
* \result La fonction renvoie 0 si aucune erreur n'est intervenue  
**************************************************/    
int Empiler (PILE *p, int valeur){

	ELEMPILE *newelem;

	newelem=(ELEMPILE *)malloc(sizeof(ELEMPILE));
	if(newelem==0) error1("Empiler: Not Enough Memory !");

	newelem->elem=valeur;
	newelem->suivant=(*p);
	(*p)=newelem;
	return(0);
	
}


/************************************************
* \brief    Retire l'element du sommet de la pile pointée par ppile et renvoie 
   sa valeur. 
* \param ppile un pointeur vers la pile 
* \pre Precondition: ppile pointe sur une pile valide
* \post Postcondition: La pile pointée par ppile a été modifiée: son premier 
          élément a été supprimé (le deuxième élément est donc devenu 
	  le sommet de pile). 
* \result Le résultat de la fonction est la 
	  valeur de l'élément supprimé si aucune erreur n'est intervenue
* \remark    Si la pile pointé par ppile est vide, la fonction affiche une erreur et interrompt le programme.
**************************************************/    
int Depiler(PILE *p){
	if((*p)!=NULL){
		int tmp = (*p)->elem;
		(*p) = (*p)->suivant;
		return tmp;
	}
	else error1("Depiler");
}

/************************************************
* \brief affiche une pile d'entier
* \param liste une liste d'entier
**************************************************/    
void afficherPile (PILE pile){
	ELEMPILE *visitor;

	visitor=pile;
	if(visitor==NULL) fprintf(stdout, "|NULL|");
	while(visitor!=0){
		fprintf(stdout, "|%d|", visitor->elem);
		visitor=visitor->suivant;
	}
	fprintf(stdout, "|--\n");

}
