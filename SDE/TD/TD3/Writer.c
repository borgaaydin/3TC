#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int grade = 0;
	int p = mknod("fifo", S_IFIFO|0666,0);
	if(p==-1){
		 fprintf(stderr,"Tube creation error ! \n");
		 exit(1);
	}
	p=open("fifo",O_WRONLY);
	if(p==-1){
		fprintf(stderr,"Tube opening error ! \n");
		exit(1);
	}
	do{
		printf("Enter the grade \n");
		scanf("%d", &grade);
		write(p,&grade,sizeof(int));
	}while(grade>=0);
	fprintf(stdout,"Pipe transaction terminated. \n");
	system("rm fifo");
	return 0;
}
