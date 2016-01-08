// KEYS OF DIFFERENT IPCs
#define KEY_MAILBOX 256 // Mailbox for vehicles
#define KEY_SHMEM 89 // Shared Memory
#define KEY_MUTEX 99 // Mutex

#define TYPE_BAL 1
#define NB_VOITURES 3

// Direction des voitures
#define NORD 0
#define EST 1
#define SUD 2
#define OUEST 3

// État des feux
#define VERT 1
#define ROUGE 0

// Mémoire partagée
#define FEUX_NORD 0
#define FEUX_EST 1
#define FEUX_SUD 2
#define FEUX_OUEST 3
#define SRC_PRIO 4
#define DEST_PRIO 5
#define ID_PRIO 6
#define PID_FEUX 7
#define PID_PRIO 8
#define PID_COORD 9

int shmem_size = sizeof(int)*10;
