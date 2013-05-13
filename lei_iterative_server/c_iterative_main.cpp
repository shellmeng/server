
#include"c_iterative_server.h"
int main()
{

     Iterative_Server iterSer=new Iterative_Server();

     printf("start server\n");
     int sockfd,connfd,n;
     pid_t pid;
     sockfd=buildConnection(PORT);
     char  rec[MAX],send[MAX];
     while(true)
     {
          connfd=accept(sockfd,NULL,NULL);
              
	  echo(connfd);
         /* if((pid=fork())==0)
          {
               close(sockfd);
               echo(connfd);
          }
          close(connfd);
	  */
     }
     close(sockfd);

}     





