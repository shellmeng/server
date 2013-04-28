#include"c_iterative_client.h"


int main(int argc,char **argv)
{
     char *addr;
     if(argc<2)
     {
          printf("usage: a IP \n");
	//  addr="127.0.0.1";
          exit(0);
	
     }

     //else
     	addr=argv[1];

     int port=PORT;
     int sockfd,n;
     sockfd=buildConnection( addr,port );
     while(1)
     {
          printf("waiting for input or network\n");
          clientReadWrite(sockfd);
     }


}


