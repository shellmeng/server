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
	 	     //printf("\n\n\n");
		     exit(0);

			  
	     }
	     else if (pid[i]==0)
	     {
		     //printf("in process %d\n",getpid());
	             ///printf("\n\n\n");
		     int count=0;

		     while(count<115)
		     {
			     signal(SIGINT,appExit);
			  printf("in process %d\n",getpid());
			  //printf("\n\n\n");
			  count++;
			  printf("*************************%d*******\n",count);
		//	  printf("\n");
		     }
		     exit(0);

	     }
	     else
	     {
		     printf("parent\n");
	     }

     
     }

    
	     sleep(1);
     printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&******\n");

}


