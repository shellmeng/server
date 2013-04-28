
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
     if(sockfd>0)
	     printf("build connection over %d\n",sockfd);
     char  rec[MAX],send[MAX];
     while(true)
     {
	  printf("waiting\n");
          connfd=accept(sockfd,NULL,NULL);
	  printf("connected from client %d\n",connfd);

	  while(1)
	  {
          FD_ZERO(&rds);
	  FD_SET(0,&rds);
	  maxfd=0;

	  tv.tv_sec=1;
	  tv.tv_usec=10;
	  FD_SET(connfd,&rds);
	  if(connfd>maxfd)
		  maxfd=connfd;

	  ret=select(maxfd+1,&rds,NULL,NULL,&tv);
	  //ret=select(maxfd+1,&rds,NULL,NULL,NULL);

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
		  printf("herre");
		  
		  if(FD_ISSET(0,&rds))
		  {

			  memset(rec,0,MAX);
			  //fgets(rec,MAX,stdin);
			  len=write(connfd,rec,strlen(rec));
			  if(len>0)
				  printf("send success\n");
			  else
				  outerr("error in send\n");
		  }
		  if(FD_ISSET(connfd,&rds))
		  {
			  memset(rec,0,MAX);
			  n=read(connfd,rec,MAX);
			  if(n>0)
			  {
				  rec[n]=0;
				  fputs(rec,stdout);
			  }
			  len=write(connfd,rec,strlen(rec));
			  if(len>0)
				  printf("send success\n");
			  else
				  outerr("error in send\n");
		  }
	  }
	  	

	  }
     }
     close(sockfd);

}     





