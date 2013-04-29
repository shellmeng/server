
#include"c_asyn_server.h"
int main()
{

     printf("start server\n");
     int sockfd,connfd,n;
     int conn2fd;

     int conns[MAX];
     int curConnNum=0;
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
          conns[0]=accept(sockfd,NULL,NULL);
	  if(conns[0]>0)
	  {
		  curConnNum++;
		  printf("connected from client %d\n",conns[0]);
	  }

	  while(1)
	  {
          FD_ZERO(&rds);
	  FD_SET(0,&rds);
	  maxfd=0;

	  FD_SET(sockfd,&rds);
	  if(sockfd>maxfd)
		  maxfd=sockfd;
	  tv.tv_sec=1;
	  tv.tv_usec=10;
	  for(int i=0;i<curConnNum;i++)
		 {
			 FD_SET(conns[i],&rds);
			 if(conns[i]>maxfd)
				 maxfd=conns[i];
		 }
	  ret=select(maxfd+1,&rds,NULL,NULL,&tv);
	  //ret=select(maxfd+1,&rds,NULL,NULL,NULL);

	  if(ret==-1)
	  {
		  outerr("select return error");
		  break;
	  }
	  else if (ret==0)
	  {
		//  outerr("select return 0, no data ready,continue");
		  continue;
	  }
	  else
	  {
		//  printf("herre");
		  
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
		  for(int i=0;i<curConnNum;i++)
		  {
			  if(FD_ISSET(conns[i],&rds))
			  {
				  memset(rec,0,MAX);
				  n=read(conns[i],rec,MAX);
				  if(n>0)
				  {
					  rec[n]=0;
					  fputs(rec,stdout);
				  }
				  len=write(conns[i],rec,strlen(rec));
				  if(len>0)
					  printf("send success\n");
				  else
					  outerr("error in send\n");
			  }
		  }

		  if(FD_ISSET(sockfd,&rds))
		  {

			  conns[curConnNum]=accept(sockfd,NULL,NULL);
			  if(conns[curConnNum]>0)
			  {
				  curConnNum++;
				  printf("a new client connected\n");
			  }
		  }
	  }
	  	

	  }
     }
     close(sockfd);

}     





