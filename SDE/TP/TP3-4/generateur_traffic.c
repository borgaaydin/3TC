#include "util.h"
#include "fifo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include "variables.h"

int
quit(){
 	exit(0);
}

int
generateur_traffic(){
	//Variable Initializations
	int identifiant = 0;
	int timer = 0;
	int dest = 0;
	int source = 0;
	int id_mailbox = -1;
	key_t key_mailbox= KEY_MAILBOX;
	MSG message;
	message.type=1;
	int indice=0;
	srand(time(NULL));

	// IPC Declarations

	if((id_mailbox = msgget(key_mailbox, IPC_CREAT|0666)) == -1) {
		printf("Coordinateur : Impossible de créer la boite aux lettres.\n");
		quit();
	}

	for(;;){
		timer = rand()%6;

		dest = (rand()%4)+1;
		source = (rand()%4)+1;

		while(source==dest) dest = ((rand()%4)+1);


		message.src=source;
		message.dest=dest;
		message.id=identifiant;
		msgsnd(id_mailbox, &message, sizeof(MSG), 0);
		printf("timer: %d, source :%d, dest :%d, id :%d\n", timer,source,dest,identifiant);
		sleep(timer);
		identifiant++;
		indice++;
	}
	return 0;
}

int main(){
	generateur_traffic();
}
