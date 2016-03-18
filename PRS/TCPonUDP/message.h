#define SYN 1
#define ACK 2
#define SYNACK 3

typedef struct Message {
   int  src_port;
   int  dest_port;
   int  seq_number;
   int  ack_number;
   int  type;
} Message;  

void createMessage(int type,int src_port, int dest_port, int seq_number, int ack_number,Message* mes){
      mes->type = type;
      mes->src_port = src_port;
      mes->dest_port = dest_port;
      mes->seq_number = seq_number;
      mes->ack_number = ack_number;
}

const char * typeConvert(int k){
  switch(k) {
   case 1 :
      return "SYN";
      break;
   case 2 :
      return "ACK";
      break;
   case 3 :
      return "SYN_ACK";
      break;
  }
}

void printMessage(Message* mes){
    printf("Received ---\n");
    printf("Type: %s \n",typeConvert(mes->type));
    printf("Source Port: %d \n",mes->src_port);
    printf("Destination Port: %d \n",mes->dest_port);
    printf("Sequence Number: %d \n",mes->seq_number);
    printf("ACK Number: %d \n",mes->ack_number);
    printf("--- --- ---\n");
}