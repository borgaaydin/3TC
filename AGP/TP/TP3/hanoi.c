#include <stdio.h>
#include "hanoi.h"
#include "pile.h"

int deplacer(PILE *source, PILE *dest) {
	int piece=Depiler(source);
	Empiler(dest, piece);
	return 0;
}

int hanoi(PILE *source,PILE *passage, PILE *dest,int N){
	if (N>1) {
		hanoi(source, dest, passage, N-1);
		deplacer(source, dest);
		hanoi(passage, source, dest, N-1);


	} else {
		deplacer(source, dest);
	}
	return 0;
}