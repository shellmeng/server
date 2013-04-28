
#include"c_asyn_server.h"
int main()
{

     printf("start server\n");
     int sockfd,connfd,n;
     pid_t pid;
     fd_set rds,wts,exps;
     int maxfd=0;
     struct timeval tv;
     int len;
     int ret;
     

     sockfd=buildConnection(PORT);
     char  rec[MAX],send[MAX];
     while(true)
     {
          connfd=accept(sockfd,NULL,NULL);
          FD_ZERO(&rds);
	  FD_SET(0,&rds);
	  maxfd=0;

	  tv.tv_sec=2;
	  tv.tv_usec=10;
	  FD_SET(connfd,&rds);
	  if(connfd>maxfd)
		  maxfd=connfd;

	  ret=select(maxfd,&rds,NULL,NULL,&tv);

	  if(ret==-1)
	  {
		  outerr("select return error");
		  break;
	  }
	  else if (ret==0)
	  {
		  outerr("select return 0, no data ready,continue");
		  continue;
	  }
	  else
	  {
		  
		  if(FD_ISSET(0,&rds))
		  {

			  memset(rec,0,MAX);
			  fgets(rec,MAX,stdin);
			  len=write(connfd,rec,strlen(rec));
			  if(len>0)
				  printf("send success\n");
			  else
				  outerr("error in send\n");
		  }
		  if(FD_ISSET(connfd,&rds))
		  {
			  memset(rec,0,MAX);
			  read(connfd,rec,MAX);
			  if(n>0)
			  {
				  rec[n]=0;
				  fputs(rec,stdout);
			  }
		  }
	  }
	  	

     }
     close(sockfd);

}     





