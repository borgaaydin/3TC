#include "arbre_type.h"
#include <stdio.h>
#include <stdlib.h>

//TODO: implementer les fonctions suivantes
/**
* \brief Fonction qui calcule la hauteur d'un arbre
* binaire donne en parametre 
* \param arbre un arbre binaire
* \return la hauteur, ie. la longueur du plus grand 
* chemin reliant la racine a une feuille de l'arbre 
*/
int hauteurArbre(ARBRE arbre){
	if(arbre == NULL){ 
		return 0;
	}
	else {
		int hautGauche = hauteurArbre(arbre->filsGauche);
		int hautDroite = hauteurArbre(arbre->filsDroit);

		if(hautGauche>hautDroite) return(hautGauche+1);
		else return(hautDroite+1);
	}
}	

/**
* \brief Fonction qui indique si l'arbre binaire passe en 
* parametre est equilibre ou non, ie. si la hauteur de son 
* sous-arbre gauche est celle de son sous-arbre droit a un
* pres et ces deux sous-arbres sont equilibres. 
* \param arbre un arbre binaire
* \return 1 s'il est equilibre, 0 sinon.  
*/
int estEquilibre (ARBRE arbre){
	if(arbre == NULL) return 1;

	int hauteurGauche = hauteurArbre(arbre->filsGauche);
	int hauteurDroite = hauteurArbre(arbre->filsDroit);

	if(abs(hauteurGauche - hauteurDroite) <= 1)
		return (estEquilibre(arbre->filsGauche) && estEquilibre(arbre->filsDroit));
	else
		return 0;
}