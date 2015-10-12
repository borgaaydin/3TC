#include <unistd.h>
#include <stdio.h>

int main(){
	int pidT[2];
	int i;
	int n = 2;
	int pidTchild1[2];
	int n1 = 2;
	
	printf("%d \n",pidT[0]);
	printf("%d \n",pidT[1]);

	if(pidT[1]!=0  && pidT[0]!=0){	
		for(i=0;i<n;i++){
			if((pidT[i]=fork())<0){
				printf("Error ! \n");	
			}else if(pidT[i]==0){
				printf("Fils %d \n",getpid());
			}
		}
	}	
	if(pidT[0]==0 && pidT[1]!=0){
		for(i=0;i<n1;i++){
			if((pidTchild1[i]=fork())<0){
				printf("Error ! \n");	
			}else if(pidTchild1[i]==0){
				printf("Fils 1 - %d \n",getpid());
			}	
		} 
	}
}
