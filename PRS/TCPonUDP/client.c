/************* UDP CLIENT CODE *******************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "message.h"


int main(){
  int clientSocket, portNum, nBytes, i;

  /* Buffers */
  Message* bufferOut;
  bufferOut = (Message*) malloc(sizeof(Message));

  Message* bufferIn;
  bufferIn = (Message*) malloc(sizeof(Message));

  /* Socket Structure */
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*Create UDP socket*/
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverAddr;

  while(1){
    createMessage(1,serverAddr.sin_port,100,1,0,bufferOut);

    sendto(clientSocket,bufferOut,6*sizeof(int),0,(struct sockaddr *)&serverAddr,addr_size);

    recvfrom(clientSocket,bufferIn,1024,0,NULL, NULL);

    printMessage(bufferIn);

    int dataFlowPort = bufferIn->dest_port;
    printf("Destination Port for transfer : %d\n", dataFlowPort);


    // for(i=0;i<10;i++)
    //   bufferOut[i] = SYN[i];
    // nBytes = strlen(bufferOut) + 1;
    // /*Send message to server*/
    // sendto(clientSocket,bufferOut,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
    // printf("Sent: %s\n",bufferOut);

    // /*Receive message from server*/
    // nBytes = recvfrom(clientSocket,bufferIn,1024,0,NULL, NULL);
    // printf("Received: %s\n",bufferIn);

    // nBytes = recvfrom(clientSocket,bufferIn,1024,0,NULL, NULL);
    // printf("Received: %s\n",bufferIn);

    // if(!strncmp("SYN",bufferIn,3)){
    //   printf("Verified: SYN\n");

    //   int seq_number = extractSeqNumber(bufferIn);
    //   printf("Extracted Sequence Number: %d\n", seq_number);

    //   for(i=0;i<3;i++)
    //     bufferOut[i] = ACK[i];

    //   bufferOut[3]='_';
    //   char seq[7];
    //   sprintf(seq, "%d", seq_number);
    //   for(i=4;i<10;i++)
    //     bufferOut[i] = seq[i-4];

    //   nBytes = strlen(bufferOut) + 1;
    //   sendto(clientSocket,bufferOut,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
    //   printf("Sent: %s\n",bufferOut);
    // }
    // else {
    //   printf("Error !\n");
    // }

    /* Reset all the buffers */
    memset(&bufferOut[0], 0, sizeof(bufferOut));
    memset(&bufferIn[0], 0, sizeof(bufferIn));

    sleep(100);
  }
  return 0;
}
