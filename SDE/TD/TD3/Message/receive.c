#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
	key_t key=100;
	int bal=msgget(KEY, IPC_CREAT|0666);
	MSG message;
	for(;;){
		printf("Waiting for grade...\n");
		msgrcv(bal, &message, 100, 1, 0);
		if(message.note<0){
			printf("All grades were input!\n");
			exit(0);
		}
		printf("Grade input: %d\n", message.note);
	}
	return 0;
}
