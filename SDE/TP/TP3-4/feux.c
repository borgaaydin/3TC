#include <stdio.h>
#include <stdlib.h> 
//#include <time.h>

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

void affichageFeux(int tab[], int size){
	for(int i=0;i<size;i++){
		if(tab[i]==0){
			printf("%s : - GREEN -\n", stringConvert(i));
		}
		else{
			printf("%s : X RED X\n", stringConvert(i));
		}
	}
}

void feux(){
	int feux[4] = {};
	int counter = 0;


	while(1){

		if(counter%2==0){
			feux[0] = 0;
			feux[1] = 1;
			feux[2] = 0;
			feux[3] = 1;
			affichageFeux(feux,4);
			printf("---------\n");
			// TODO:envoi a mem part
		}
		else {
			feux[0] = 1;
			feux[1] = 0;
			feux[2] = 1;
			feux[3] = 0;
			affichageFeux(feux,4);
			printf("---------\n");
			// TODO:envoi a mem part
		}
		counter++;
		sleep(5);
	}
}

int main(){
	feux();
}