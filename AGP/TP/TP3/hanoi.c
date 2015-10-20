#include <stdio.h>
#include "hanoi.h"

void deplacer(PILE depart, PILE arrivee) {
	int piece=depiler(depart);
	empiler(arrivee);
}

void hanoi(PILE depart, PILE arrivee, PILE passage, int N){
	if (N>1) {
		hanoi(depart, passage, arrivee, N-1);
		deplacer(depart, arrivee);
		hanoi(passage, arrivee, depart, N-1);
	} else {
		deplacer(depart, arrivee);
	}
}