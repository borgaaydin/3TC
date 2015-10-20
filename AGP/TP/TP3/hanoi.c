#include <stdio.h>
#include "hanoi.h"

void deplacer(PILE *source, PILE *dest) {
	int piece=depiler(source);
	empiler(dest);
}

void hanoi(PILE *source, PILE *dest, PILE *passage, int N){
	if (N>1) {
		hanoi(source, passage, dest, N-1);
		deplacer(source, dest);
		hanoi(passage, dest, source, N-1);
	} else {
		deplacer(source, dest);
	}
}