	#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>

#include "variables.h"
#include "shmem.h"
#include "semaphore.h"

int id_shmem;
int* pshmem;

void quit() {
    printf("generateurTrafficPrioritaire : Je meurs.\n");
		pshmem[SRC_PRIO] = 0;
		pshmem[DEST_PRIO] = 0;
		pshmem[ID_PRIO] = 0;
		pshmem[PID_PRIO] = 0;
    remove_shmem(id_shmem);
    exit(0);
}

void generateurTrafficPrioritaire(){

	key_t key_shmem = KEY_SHMEM;

	// Attachement à la shmem
	if((id_shmem = open_shmem(key_shmem, shmem_size)) == -1) {
			printf("generateurTrafficPrioritaire : Impossible d'ouvrir la mémoire partagée.\n");
			quit();
	}
	if((pshmem = attach_shmem(id_shmem)) == -1) {
			printf("generateurTrafficPrioritaire : Impossible de s'attacher à la mémoire partagée.\n");
			quit();
	}
	pshmem[SRC_PRIO] = 0;
	pshmem[DEST_PRIO] = 0;
	pshmem[ID_PRIO] = 0;

	pshmem[PID_PRIO]=getpid();
	int pid_coord = pshmem[PID_COORD];
	printf("PID generPrio : %d\n", getpid());
	printf("PID Coord : %d\n", pid_coord);


	int timer, source, dest, id=0;
	srand(time(NULL));
	for(int j=0;j<2;j++){
		timer=rand()%26;
		while(timer<15){
			timer=rand()%26;
		}
		printf("Timer is UP: %d s\n", timer);
		sleep(timer);
		printf("Timer is DOWN: %d s\n", timer);
		source=(rand()%4)+1;
		dest=(rand()%4)+1;
		while(dest==source){
			dest=(rand()%4)+1;
		}

		pshmem[SRC_PRIO] = source;
		pshmem[DEST_PRIO] = dest;
		pshmem[ID_PRIO] = id;

    	kill(pid_coord, SIGUSR1);
		printf("! --- PRIORITAIRE --- ! Source: %d, Dest: %d, ID :%d\n", source, dest, id);
		printf("Coordinateur is notified by signal !\n");
		id++;
	}
}

int main(){
	generateurTrafficPrioritaire();
}
