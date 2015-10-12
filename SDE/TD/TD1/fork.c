#include <unistd.h>
int main() {
	int pid;
	int x = 0;
	pid=fork();
	while(x<10){
		if(pid==0) printf("Je suis le fils : %d \n",x);
		else if(pid>0) printf("Je suis le pere : %d \n",x);
		else perror("Creation processus");	
		x++;
	}
}
