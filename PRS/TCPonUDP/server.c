
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"

int main(){
  int udpSocket, nBytes;
  Message* bufferIn;
  bufferIn = (Message*) malloc(sizeof(Message));

  Message* bufferOut;
  bufferOut = (Message*) malloc(sizeof(Message));

  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;

  /*Create UDP socket*/
  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

  /*Bind socket with address struct*/
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverStorage;

  while(1){
    /* Try to receive any incoming UDP datagram. Address and port of
      requesting client will be stored on serverStorage variable */
    recvfrom(udpSocket,bufferIn,6*sizeof(int),0,(struct sockaddr *)&serverStorage, &addr_size);
    printMessage(bufferIn);

    if(bufferIn->type==SYN){
      createMessage(SYNACK,serverAddr.sin_port,5656,bufferIn->seq_number+1,bufferIn->ack_number,bufferOut);
      sendto(udpSocket,bufferOut,6*sizeof(int),0,(struct sockaddr *)&serverStorage,addr_size);
    }

    recvfrom(udpSocket,bufferIn,6*sizeof(int),0,(struct sockaddr *)&serverStorage, &addr_size);
    printMessage(bufferIn);

    sleep(100);
  }

  /* Reset all the buffers */
  memset(&bufferOut[0], 0, sizeof(bufferOut));
  memset(&bufferIn[0], 0, sizeof(bufferIn));
  return 0;
}
