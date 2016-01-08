#ifndef UTIL_H
#define UTIL_H

struct fifo {
	int src;
	int dest;
	int id;
	struct fifo* next;
};

typedef struct fifo FIFO;

struct message {
	long type;
	int src;
	int dest;
	int id;
};

typedef struct message MSG;

const char * stringConvert(int indice) {
    switch(indice) {
    	case 0 :
    		return "NORTH";
    		break;
    	case 1 :
    		return "EAST";
    		break;
    	case 2 :
    		return "SOUTH";
    		break;
    	case 3 :
    		return "WEST";
    		break;
    }
}

#endif
