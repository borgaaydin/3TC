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
	pshmem[PID_COORD] = 0;
  msgctl(id_mailbox, IPC_RMID, NULL);
	remove_shmem(id_shmem);
	exit(0);
}

void prioritaire(){
		printf("Coordinateur : Priority vehicle coming in hot. Changing the traffic lights\n");
		kill(PID_FEUX, SIGUSR2);
		printf("Coordinateur : Only the cars on the lane of priority are passing.\n");
		pshmem[SRC_PRIO] = source;
		pshmem[DEST_PRIO] = dest;
		pshmem[ID_PRIO] = id;
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
	pshmem[PID_COORD] = getpid();

	fprintf(stdout, "PID feux : %d\n", pid_feux);
	fprintf(stdout, "PID Coord : %d\n", getpid());

	FIFO* fifo1=NULL;
	FIFO* fifo2=NULL;
	FIFO* fifo3=NULL;
	FIFO* fifo4=NULL;

	signal(SIGUSR1, prioritaire);

	for(;;){
		msgrcv(id_mailbox, &message, sizeof(MSG), 1, 0);
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
		if(pshmem[0]==0 && pshmem[2]==0){
			priorite(fifo1, fifo3, 0);
			fifo1=delNode(fifo1);
			fifo3=delNode(fifo3);
		}else{
			priorite(fifo2, fifo4, 1);
			fifo2=delNode(fifo2);
			fifo4=delNode(fifo4);
		}
	}
	//TODO: destroy IPCs
}

void priorite(FIFO* fifo1, FIFO* fifo2, int feux){
	if(fifo1!=0){
		if((feux==0 && (fifo1->dest==3 || fifo1->dest==2)) || (feux==1 && (fifo1->dest==0 || fifo1->dest==3))){
				printf("\nCar #%d is going from %s to %s", fifo1->id, stringConvert(fifo1->src), stringConvert(fifo1->dest));
				if(fifo2!=0){
					printf("\nCar #%d is going from %s to %s", fifo2->id, stringConvert(fifo2->src), stringConvert(fifo2->dest));
				}
			}
			else{
				if(fifo2!=0){
					printf("\nCar #%d is going from %s to %s", fifo2->id, stringConvert(fifo2->src), stringConvert(fifo2->dest));
				}
				printf("\nCar #%d is going from %s to %s", fifo1->id, stringConvert(fifo1->src), stringConvert(fifo1->dest));
		}
	}
	else{
		if (fifo2!=NULL){
			printf("\nCar #%d is going from %s to %s", fifo2->id, stringConvert(fifo2->src), stringConvert(fifo2->dest));
		}
	}
}

int main(){
	coordinateur();
	return 0;
}
