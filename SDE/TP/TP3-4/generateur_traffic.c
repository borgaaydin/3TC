#include "util.h"
#include "fifo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
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

	key_t keyBal=100;
	int bal=msgget(keyBal, IPC_CREAT|0666);
	MSG message;
	message.type=1;
	int indice=0;
	for(;;){
		timer = rand()%6;

		dest = (rand()%4)+1;
		source = (rand()%4)+1;

		while(source==dest) dest = ((rand()%4)+1);

		printf("timer: %d, source :%d, dest :%d\n", timer,source,dest);
		FIFO* car=newNode(source, dest, identifiant);
		message.car=car;
		printf("\n%d %d %d\n", message.car->src, message.car->dest, message.car->id);
		msgsnd(bal, &message, sizeof(message), 0);
		printf("\nHey!\n");
		sleep(timer);
		identifiant++;
		indice++;
	}
	return 0;
}

int main(){
	generateur_traffic();
}
