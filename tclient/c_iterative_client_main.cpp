#include"c_iterative_client.h"


int main(int argc,char **argv)
{
     if(argc<2)
     {
          printf("usage: a IP \n");
          exit(0);
     }

     char *addr=argv[1];
     int port=PORT;
     int sockfd,n;
     sockfd=buildConnection( addr,port );
     while(1)
     {
          printf("waiting for input or network\n");
          clientReadWrite(sockfd);
     }


}


