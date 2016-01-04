	#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void generateurTrafficPrioritaire(){
	int timer, source, dest, i=0;
	srand(time(NULL));
	for(int j=0;j<10;j++){
		timer=rand()%26;
		while(timer<15){
			timer=rand()%26;
		}
		printf("Timer: %d\n", timer);
		source=(rand()%4)+1;
		dest=(rand()%4)+1;
		while(dest==source){
			dest=(rand()%4)+1;
		}
		printf("Source: %d, Dest: %d\n", source, dest);
		// sleep(timer);
		i++;
	}
}

int main(){
	generateurTrafficPrioritaire();
}
