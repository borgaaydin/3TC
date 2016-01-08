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

	FIFO* fifo1=NULL;
	FIFO* fifo2=NULL;
	FIFO* fifo3=NULL;
	FIFO* fifo4=NULL;

	signal(SIGUSR1, prioritaire);

	for(;;){
		msgrcv(id_mailbox, &message, sizeof(MSG), 1, 0);
		printf("\n%d\n", message.dest);
		FIFO* car=newNode(message.src, message.dest, message.id);
		switch(car->src){
			case 1:
				printf("\nAdding to fifo1\n");
				fifo1=addNode(fifo1, car);
				break;
			case 2:
				printf("\nAdding to fifo2\n");
				fifo2=addNode(fifo2, car);
				break;
			case 3:
				printf("\nAdding to fifo3\n");
				fifo3=addNode(fifo3, car);
				break;
			case 4:
				printf("\nAdding to fifo4\n");
				fifo4=addNode(fifo4, car);
				break;
		}
		if(pshmem[0]==0 && pshmem[2]==0){
			printf("\nFeux 1 et 3 verts");
			if(fifo1!=NULL){
				printf("\nCar #%d is going from %d to %d\n", fifo1->id, fifo1->src, fifo1->dest);
				fifo1=fifo1->next;
			}
			if(fifo3!=NULL){
				printf("\nCar #%d is going from %d to %d\n", fifo3->id, fifo3->src, fifo3->dest);
				fifo3=fifo3->next;
			}
		}else{
			printf("\nFeux 2 et 4 verts");
			if(fifo2!=NULL){
				printf("\nCar #%d is going from %d to %d\n", fifo2->id, fifo2->src, fifo2->dest);
				fifo2=fifo2->next;
			}
			if(fifo4!=NULL){
				printf("\nCar #%d is going from %d to %d\n", fifo4->id, fifo4->src, fifo4->dest);
				fifo4=fifo4->next;
			}
		}
	}
	//TODO: destroy IPCs
}

int main(){
	coordinateur();
	return 0;
}
