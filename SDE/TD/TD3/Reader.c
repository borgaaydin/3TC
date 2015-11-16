#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int grade;
	int k = open("fifo",O_RDONLY);
	if(k == -1){
		fprintf(stderr,"Tube opening error ! \n");
		exit(1);
	}
	read(k,&grade,sizeof(int));
	while(grade>=0){	
		int p = open("fifo",O_RDONLY);
		if(p==-1){
			fprintf(stderr,"Tube opening error ! \n");
			exit(1);
		}
		read(p,&grade,sizeof(int));
		fprintf(stdout, "Grade is : %d \n",grade);
		close(p);
	}
	return 0;
}
