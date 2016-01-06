#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <signal.h>
#include "util.h"
#include "fifo.h"
#include "coordinateur.h"
#include "variables.h"
#include "shmem.h"
#include "semaphore.h"


int id_shmem;
int* pshmem;
int id_mailbox;


void quit(){

}

void prioritaire(){
		printf("Coordinateur : Priority vehicle coming in hot. Changing the traffic lights\n");
		kill(PID_FEUX, SIGUSR2);
		printf("Coordinateur : Only the cars on the lane of priority are passing.\n");
		//Lookup for the information about priority vehicle in the shared memory.

}

void coordinateur(){
	MSG message;
	int f1, f2, f3, f4;
	key_t key_mailbox = KEY_MAILBOX;
	key_t key_shmem = KEY_SHMEM;

	if((id_mailbox = msgget(key_mailbox, IPC_CREAT|0666)) == -1) {
		printf("Coordinateur : Impossible de créer la boite aux lettres.\n");
		quit();
	}

	if((id_shmem = create_shmem(key_shmem, shmem_size)) == -1) {
		printf("Coordinateur : Impossible de créer la mémoire partagée.\n");
		quit();
	}

	// Attachement à la shmem
	if((pshmem = attach_shmem(id_shmem)) == -1) {
		printf("Coordinateur : Impossible de s'attacher à la mémoire partagée.\n");
		quit();
	}

	while(pshmem[PID_FEUX] == 0){
		fprintf(stdout, "Waiting for PID_FEUX ...\n" );
		sleep(1);
	}

	// while(msgrcv(id_mailbox, &message, sizeof(MSG), 1, 0) == -1){
	// 	fprintf(stdout, "Waiting for MAILBOX ! ...\n" );
	// 	sleep(1);
	// }

	int pid_feux = pshmem[PID_FEUX];
	fprintf(stdout, "PID FEUX : %d\n", pid_feux);

	FIFO* fifo1=(FIFO*)(malloc(sizeof(FIFO)));
	FIFO* fifo2=(FIFO*)(malloc(sizeof(FIFO)));
	FIFO* fifo3=(FIFO*)(malloc(sizeof(FIFO)));
	FIFO* fifo4=(FIFO*)(malloc(sizeof(FIFO)));

	signal(SIGUSR1, prioritaire);

	for(;;){
		msgrcv(id_mailbox, &message, sizeof(MSG), 1, 0);
		printf("\n%d\n", message.dest);
		FIFO* car=newNode(message.src, message.dest, message.id);
		switch(car->src){
			case 1:
				fifo1=addNode(fifo1, car);
				break;
			case 2:
				fifo2=addNode(fifo2, car);
				break;
			case 3:
				fifo3=addNode(fifo3, car);
				break;
			case 4:
				fifo4=addNode(fifo4, car);
				break;
		}
		passage();
	}
	//TODO: destroy IPCs
}

void passage(){

}

int main(){
	coordinateur();
	return 0;
}
