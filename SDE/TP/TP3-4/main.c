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

// TESTs
int main() {
  fprintf(stdout, "TEST 1 : IPC \n" );


  fprintf(stdout, "TEST 2 : FIFO \n" );
    

}
