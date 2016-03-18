/************* UDP SERVER CODE *******************/

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

    // removeSpaces(bufferIn);

    // if(!strncmp("SYN",bufferIn,3)){
    //   printf("Verified: SYN \n");

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
    //   /*Send uppercase message back to client, using serverStorage as the address*/
    //   sendto(udpSocket,bufferOut,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
    //   printf("Sent: %s \n",bufferOut);

    //   seq_number++;

    //   for(i=0;i<3;i++)
    //     bufferOut[i] = SYN[i];
    //   sprintf(seq, "%d", seq_number);
    //   for(i=4;i<10;i++)
    //     bufferOut[i] = seq[i-4];

    //   nBytes = strlen(bufferOut) + 1;

    //   sendto(udpSocket,bufferOut,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
    //   printf("Sent: %s \n",bufferOut);
    // }



    // nBytes = recvfrom(udpSocket,bufferIn,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
    // printf("Received: %s \n",bufferIn);

    // removeSpaces(bufferIn);

    // if(strncmp("ACK",bufferIn,3)){
    //   printf("Verified: ACK \n");
    //   printf("START FILE TRANSFER ! \n");

    //   recvfrom(udpSocket,bufferIn,1024,0,(struct sockaddr *)&serverStorage, &addr_size);

    //   // FILE *fp = fopen(bufferIn, "r");
    //   // if (fp == NULL) {
    //   //     printf("File does not exist \n");
    //   //     return 1;
    //   // }
    //   //
    //   // while (1) {
    //   //     bytes_read = read(fp, content, sizeof(content));
    //   //     if (bytes_read == 0)
    //   //         break;
    //   //     sendto(sd, content, sizeof(content), 0, (struct sockaddr*)&cliaddr, len);
    //   //     bzero(content, 200);
    //   // }

    //   sleep(100);
    // }


  }
  return 0;
}
