#include <stdio.h>
#include "hanoi.h"

int deplacer(PILE *source, PILE *dest) {
	int piece=depiler(source);
	empiler(dest);
	return 0;
}

int hanoi(PILE *source, PILE *dest, PILE *passage, int N){
	if (N>1) {
		hanoi(source, passage, dest, N-1);
		deplacer(source, dest);
		hanoi(passage, dest, source, N-1);
	} else {
		deplacer(source, dest);
	}
	return O;
}