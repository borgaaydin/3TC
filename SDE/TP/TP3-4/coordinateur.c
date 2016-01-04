#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "message.h"
#include "fifo.h"
#include "coordinateur.h"

void coordinateur(){
	key_t keyBal=100, keyMem=200;
	int bal=msgget(keyBal, IPC_CREAT|0666);
	int shmid=shmget(keyMem, sizeof(int)*8, IPC_CREAT|0777);
	int* feux=(int*) shmat(shmid, 0, 0);
	FIFO* fifo1=init();
	FIFO* fifo2=init();
	FIFO* fifo3=init();
	FIFO* fifo4=init();
	//TODO: arm signal SIGUSR1
	int f1, f2, f3, f4;
	MSG message;
	for(;;){
		f1=feux[1];
		f2=feux[2];
		f3=feux[3];
		f4=feux[4];
		msgrcv(bal, &message, 100, 1, 0);
		switch(message.src){
			case 1:
				add(fifo1, message.src, message.dest, message.id);
				break;
			case 2:
				add(fifo2, message.src, message.dest, message.id);
				break;
			case 3:
				add(fifo3, message.src, message.dest, message.id);
				break;
			case 4:
				add(fifo4, message.src, message.dest, message.id);
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
