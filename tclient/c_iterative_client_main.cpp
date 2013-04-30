#include"c_iterative_client.h"

#define FORKNUM 4
#define REQUESTNUM 20

int main(int argc,char **argv)
{
     char *addr;
     if(argc<2)
     {
          printf("usage: a IP \n");
	  addr="127.0.0.1";
         // exit(0);
	
     }

     else
     	addr=argv[1];

     int port=PORT;
     int sockfd,n;

     int clientsocks[FORKNUM];
     pid_t pid[FORKNUM];


     for(int i=0;i< FORKNUM;i++)
     {

	     if( (pid[i]=fork())<0)
	     {
		     printf("fork error\n");
		     exit(0);

			  
	     }
	     else if (pid[i]==0)
	     {
		     printf("in process %d\t",getpid());
		     int count=0;

		     clientsocks[i]=buildConnection( addr,port );
		     while(count<REQUESTNUM)
		     {
			  count++;
			  printf("***********************************%d*******\n",count);
			  clientReadWrite(clientsocks[i]);
		     }
		     exit(0);

	     }

     
     }

//     sleep(15);
     for(int i=0;i<FORKNUM;i++)
	     wait(NULL);

    
//     printf("*********&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&7***************************************************\n");

     return 0;
}


