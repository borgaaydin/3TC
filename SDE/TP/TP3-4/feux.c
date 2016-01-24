#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>

#include "variables.h"
#include "shmem.h"
#include "semaphore.h"

#include "feux.h"

int id_mutex;
int id_shmem;
int* pshmem;

void quit() {
    printf("Feux : Je meurs.\n");
    down(id_mutex);
    pshmem[PID_FEUX] = 0;
    up(id_mutex);
    remove_shmem(id_shmem);
    exit(0);
}

void priority(){
    int feuxPrioritaire[4] = {};
    int src = 0, dest = 0, id = 0;
    src = pshmem[SRC_PRIO];
    dest = pshmem[DEST_PRIO];
    id = pshmem[ID_PRIO];

    printf("Src Prio : %d, Dest Prio : %d, ID Prio : %d \n", src,dest,id);

    down(id_mutex);
    for(int k = 0; k<4;k++){
        feuxPrioritaire[k] = 1; // Turn red all the lights
    }
    feuxPrioritaire[src] = 0; // Turn green the priority lane
    affichageFeux(feuxPrioritaire,4);

    //Put the state of lights into the Shared Memory
    for(int k = 0; k<4;k++){
        pshmem[k]=feuxPrioritaire[k];
    }
    up(id_mutex);

    printf("!!! --- priority --- !!!\n");

    affichageFeux(feuxPrioritaire,4);
}

const char * stringConvert(int indice) {
    switch(indice) {
    	case 0 :
    		return "NORTH (1)";
    		break;
    	case 1 :
    		return "EAST (2)";
    		break;
    	case 2 :
    		return "SOUTH (3)";
    		break;
    	case 3 :
    		return "WEST (4)";
    		break;
    }
}

void affichageFeux(int tab[], int size){
	for(int i=0;i<size;i++){
		if(tab[i]==0){
			printf("%s : - GREEN -\n", stringConvert(i));
		}
		else{
			printf("%s : X RED X\n", stringConvert(i));
		}
	}
	printf("---------\n");
}

void feux(){
	int feux[4] = {};
	int counter = 0;

	while(1){
  		if(counter%2==0){
      down(id_mutex);
			feux[0] = 0;
			feux[1] = 1;
			feux[2] = 0;
			feux[3] = 1;

      for(int k = 0; k<4;k++){
        pshmem[k]=feux[k];
      }
      up(id_mutex);
			affichageFeux(feux,4);
		}
		else {
      down(id_mutex);
			feux[0] = 1;
			feux[1] = 0;
			feux[2] = 1;
			feux[3] = 0;


      for(int k = 0; k<4;k++){
        pshmem[k]=feux[k];
      }
      up(id_mutex);
			affichageFeux(feux,4);
		}
		counter++;
		sleep(5);
	}
}

int main(){
  signal(SIGQUIT, quit);
  signal(SIGINT, quit);

  signal(SIGUSR2, priority);
  signal(SIGUSR1, feux);

  key_t cle_shmem = KEY_SHMEM;
  key_t key_mutex = KEY_MUTEX;

  if((id_mutex = open_semaphore(key_mutex)) == -1) {
			printf("Impossible d'ouvrir le mutex.\n");
			quit();
	}

  if((id_shmem = open_shmem(cle_shmem, shmem_size)) == -1) {
      printf("Feux : Impossible d'ouvrir la mémoire partagée.\n");
      quit();
  }
  if((pshmem = attach_shmem(id_shmem)) == -1) {
      printf("Feux : Impossible de s'attacher à la mémoire partagée.\n");
      quit();
  }
  printf("PID Feux : %d\n", getpid());

  down(id_mutex);
  pshmem[PID_FEUX]=getpid();
  up(id_mutex);

	feux();
}
