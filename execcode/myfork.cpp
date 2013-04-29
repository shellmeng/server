#include"../netHeader.h"
#include<signal.h>




#define FORKNUM 3

void appExit(int a )
{
	exit(0);
}


int main(int argc,char **argv)
{
     int clientsocks[FORKNUM];
     pid_t pid[FORKNUM];



     signal(SIGINT,appExit);
     for(int i=0;i< FORKNUM;i++)
     {

	     if( (pid[i]=fork())<0)
	     {
		     printf("fork error\n");
		     exit(0);

			  
	     }
	     else if (pid[i]==0)
	     {
		     signal(SIGINT,appExit);
		     printf("in process %d\n\n",getpid());
		     int count=0;

		     while(1)
		     {
			  printf("in process %d\n\n",getpid());
			  count++;
			  printf("*************************%d*******\n\n",count);
		     }
		     exit(0);

	     }

     
     }

    
     printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&******\n");

}


