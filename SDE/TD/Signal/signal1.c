#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int);

int main()
{
	int pid = 0;
	pid=fork();
	if(pid==0){
		while(1) 
		{
			signal(SIGINT, sighandler);
			printf("Je suis le fils : \n");
			printf("Going to sleep for a second...\n");
			sleep(1); 
		}
	}
	else if(pid>0){ 
		signal(SIGINT, sighandler);
		while(1) 
		{
			printf("Je suis le pere : \n");
			printf("Going to sleep for 5 second...\n");
			sleep(5);
		}
	}
	else perror("Creation processus");	

	return(0);
}

void sighandler(int signum)
{
   printf("Caught signal %d, coming out...\n", signum);
   exit(1);
}