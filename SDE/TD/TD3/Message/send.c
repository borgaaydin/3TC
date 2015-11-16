#include "message.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(){
	key_t key=100;
	int bal=msgget(key, IPC_CREAT|0666);
	MSG message;
	message.type=1;
	do {
		scanf("%d", &message.note);
		msgsnd(bal, &message, sizeof(message.note), 0);
	} while(message.note>0);
	sleep(5);
	msgctl(bal, IPC_RMID, 0);
	return 0;
}