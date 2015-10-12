#include <unistd.h>
#include <stdlib.h>

int main() {
	
	int pid,number,status;
	pid=fork();
	if(pid==0) {
	/*Le fils*/
		printf("Tapez un numero ! \n");
		scanf("%d",&number);
		exit(number);
	}else if(pid>0){
	/*Le pere*/
		pid = wait(&status);
		printf("%d \n",WEXITSTATUS(status));
	}	

}
