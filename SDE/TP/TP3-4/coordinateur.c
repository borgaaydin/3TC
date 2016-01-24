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

int id_mutex;
int id_shmem;
int* pshmem;
int id_mailbox;

void quit(){
	down(id_mutex);
	pshmem[PID_COORD] = 0;
	up(id_mutex);
	
  msgctl(id_mailbox, IPC_RMID, NULL);
	remove_shmem(id_shmem);
	exit(0);
}

void prioritaire(){
		int srcPrio, destPrio, idPrio;
		int pid_feux = pshmem[PID_FEUX];
		printf("Coordinateur: Priority vehicle is coming in hot. Changing the traffic lights!\n");
		kill(pid_feux, SIGUSR2);
		printf("Coordinateur: Only the cars on the lane of priority are passing.\n");

		down(id_mutex);
		srcPrio = pshmem[SRC_PRIO] ;
		destPrio =pshmem[DEST_PRIO];
		idPrio = pshmem[ID_PRIO] ;
		up(id_mutex);

		sleep(5);
		printf("Waiting to send sigusr1.\n");
		printf("Priority vehicle #%d is going from %d to %d\n", idPrio, srcPrio, destPrio);
		kill(pid_feux, SIGUSR1);
		printf("SIGUSR1 is sent to FEUX.\n");
		printf("priority is finished...\n");
}

void coordinateur(){
	MSG message;
	int f1, f2, f3, f4;

	key_t key_mailbox = KEY_MAILBOX;
	key_t key_shmem = KEY_SHMEM;
	key_t key_mutex = KEY_MUTEX;

	if((id_mailbox = msgget(key_mailbox, IPC_CREAT|0666)) == -1) {
		printf("Coordinateur : Impossible de créer la boite aux lettres.\n");
		quit();
	}

	if((id_shmem = create_shmem(key_shmem, shmem_size)) == -1) {
		printf("Coordinateur : Impossible de créer la mémoire partagée.\n");
		quit();
	}

	if((pshmem = attach_shmem(id_shmem)) == -1) {
		printf("Coordinateur : Impossible de s'attacher à la mémoire partagée.\n");
		quit();
	}

	if((id_mutex = create_semaphore(key_mutex)) == -1) {
		printf("Impossible de créer le mutex.\n");
		quit();
	}

	if(init_semaphore(id_mutex, 1) == -1) {
		printf("Impossible d'initialiser le mutex.\n");
		quit();
	}

	while(pshmem[PID_FEUX] == 0){
		fprintf(stdout, "Waiting for PID_FEUX ...\n" );
		sleep(1);
	}

	int pid_feux = pshmem[PID_FEUX];

	down(id_mutex);
	pshmem[PID_COORD] = getpid();
	up(id_mutex);

	fprintf(stdout, "PID feux : %d\n", pid_feux);
	fprintf(stdout, "PID Coord : %d\n", getpid());

	FIFO* fifo1=NULL;
	FIFO* fifo2=NULL;
	FIFO* fifo3=NULL;
	FIFO* fifo4=NULL;

	signal(SIGUSR1, prioritaire);

	for(;;){
		printf("---+--- Mailbox is empty, waiting for a new message\n");
		sleep(1);
		int msgReturn = msgrcv(id_mailbox, &message, sizeof(MSG), 1, 0);
		if(msgReturn != -1) {
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
	}
}

void priorite(FIFO* fifo1, FIFO* fifo2, int feux){
	if(fifo1!=0){
		if((feux==0 && (fifo1->dest==3 || fifo1->dest==2)) || (feux==1 && (fifo1->dest==0 || fifo1->dest==3))){
				printf("Car #%d is going from %d to %d\n", fifo1->id, fifo1->src, fifo1->dest);
				if(fifo2!=0){
					printf("Car #%d is going from %d to %d\n", fifo2->id, fifo2->src, fifo2->dest);
				}
			}
			else{
				if(fifo2!=0){
					printf("Car #%d is going from %d to %d\n", fifo2->id, fifo2->src, fifo2->dest);
				}
				printf("Car #%d is going from %d to %d\n", fifo1->id, fifo1->src, fifo1->dest);
		}
	}
	else{
		if (fifo2!=NULL){
			printf("Car #%d is going from %d to %d\n", fifo2->id, fifo2->src, fifo2->dest);
		}
	}
}

int main(){
	coordinateur();
	return 0;
}
