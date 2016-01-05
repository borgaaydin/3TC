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

void prioritaire(){
		printf("Coordinateur : Priority vehicle coming in hot. Changing the traffic lights\n");
		kill(PID_FEUX, SIGUSR2);
		printf("Coordinateur : Only the cars on the lane of priority are passing.\n");
		//Lookup for the information about priority vehicle in the shared memory.

}

void coordinateur(){
	key_t keyBal=100, keyMem=200;
	int bal=msgget(keyBal, IPC_CREAT|0666);
	int shmid=shmget(keyMem, sizeof(int)*8, IPC_CREAT|0777);
	int* feux=(int*) shmat(shmid, 0, 0);

	FIFO* fifo1=init();
	FIFO* fifo2=init();
	FIFO* fifo3=init();
	FIFO* fifo4=init();

  signal(SIGUSR1, prioritaire);

	int f1, f2, f3, f4;
	MSG message;
	for(;;){
		f1=feux[1];
		f2=feux[2];
		f3=feux[3];
		f4=feux[4];
		msgrcv(bal, &message, 100, 1, 0);
		switch(message.car->src){
			case 1:
				addNode(fifo1, message.car);
				break;
			case 2:
				addNode(fifo2, message.car);
				break;
			case 3:
				addNode(fifo3, message.car);
				break;
			case 4:
				addNode(fifo4, message.car);
				break;
		}
		passage();
	}
	//TODO: destroy IPCs
}

void passage(){

}

int main(){
	printf("\nI'm here\n");
	coordinateur();
	return 0;
}
