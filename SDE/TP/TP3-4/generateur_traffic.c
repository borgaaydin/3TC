#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int
quitter(){

return 0;
}

int
generateur_traffic(){
	int identifiant = 0;
	int timer = 0;
	int dest = 0;
	int source = 0;
	srand(time(NULL));

	int indice=0;
	while(indice<=10){


		timer = rand()%6;

		dest = (rand()%4)+1;
		source = (rand()%4)+1;

		while(source==dest) dest = ((rand()%4)+1);

		printf("timer: %d, source :%d, dest :%d\n", timer,source,dest);

		identifiant++;
		indice++;
	}
	return 0;
}

int main(){
	generateur_traffic();
}