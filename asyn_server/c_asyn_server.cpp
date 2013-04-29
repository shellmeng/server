
#include"c_asyn_server.h"
fd_set rds,wts,exps;
int conns[MAX];
char ** bufsRead=(char **)malloc(sizeof(char *) *MAX);
char ** bufsWrite=(char **)malloc(sizeof(char *) *MAX);
int curConnNum=0;

int buildConnection(int port)
{
     int sockfd;
     struct sockaddr_in server,client;

     if ((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
     {
          outerr("new socket error in server\n");
          exit(-1);
     }

     bzero(&server,sizeof(server));

     server.sin_family=AF_INET;
     server.sin_port=htons(port);
     server.sin_addr.s_addr=htonl(INADDR_ANY);
    
     bind(sockfd,(struct sockaddr*)&server,sizeof(server));
     setsockopt(sockfd,SOL_SOCKET ,SO_REUSEADDR,(const char*)&server,sizeof(bool));
     listen(sockfd,LISTENQUE);

     return sockfd;

}



/*int echo(int conn)
{
     int n;

     char line[MAX];
     int count=0;
     while(true)
     {
          printf("%d\n",count++);
          n=read(conn,line,MAX);
          printf("server: n=%d\n",n);
          if(n==0)
          {
               return 0;
          }
	  line[n]=0;
          write(conn,line,strlen(line));
     }
     printf("exit echo\n");
}
*/
/*
 copy the data from bufsRead[i] to bufsWrite[i]
 always return 1 because the operation is so easy and error is hard to make
 */
int handleData(int clientNum)
{
	memset(bufsWrite[clientNum],0,MAX);
	memcpy(bufsWrite[clientNum],bufsRead[clientNum],strlen(bufsRead[clientNum]) );
	return 1;
			
}
/* 
receive data from socket conns[clientNum], and the data are stored in the bufsRead[clientNum] 
return 1 if everything is ok
return -1 is there is somethign wrong ,but wouldn't exit
 */
int receiveData(int clientNum)
{

  int ret;
  int n;
  memset(bufsRead[clientNum],0,MAX);
  n=read(conns[clientNum],bufsRead[clientNum],MAX-1);
  if(n>0)
  {
	  bufsRead[clientNum][n]=0;
	  puts(bufsRead[clientNum]);
	  ret=handleData(clientNum);
	  if(ret!=1)
	  {
		  outerr("error in hanleData");
		  exit(0);
	  }
	  return 1;
  }
  else
  {

	  outerr("the receive didnot received data");
	  return -1;
  }
}

int sendData(int clientNum)
{
	printf("in sendData\n");
	char * start=bufsWrite[clientNum];
	int n=0;
	if(strlen(start)>0)
		//n=write(conns[clientNum],bufWrite[clientNum],strlen(bufWrite[clientNum];
	{
		printf("the data in bufs is\n");
		puts(start);
		n=write(conns[clientNum],start,strlen(start));
		if(n==strlen(start) )
		{
			printf("yes, all sended\n");
			bufsWrite[clientNum][0]=0;
		}
		else if(n>0 &&n<strlen(start))
		{
			start+=n;
			memcpy(bufsWrite[clientNum],start,strlen(start));
			printf("partly sended\n");
		}
		else if(n<1)
		{
			outerr("error in sendData");
			return -1;
		}
		return 1;

	}
	else
	{
	//	outerr("no data to send");
		return 0;
	}

		
}

int doselect(int listenSock)
{
     int sockfd,n;
     sockfd=listenSock;
     int maxfd=0;
     struct timeval tv;
     int len;
     int ret;
     

     memset(bufsRead,0,MAX);
     memset(bufsWrite,0,MAX);

     if(sockfd<=0)
     {
	     outerr("not listening");
	     exit(0);
     }
     char  rec[MAX],send[MAX];
     while(true)
     {
	  printf("waiting\n");
          conns[0]=accept(sockfd,NULL,NULL);
	  if(conns[0]>0)
	  {
		  curConnNum++;
		  bufsRead[0]=(char *)malloc(sizeof(char )*MAX);
		  bufsWrite[0]=(char *)malloc(sizeof(char )*MAX);
		  /*for(int i=0;i<curConnNum;i++)
		  {
			  if(bufsRead[i]!=NULL)
			  {
				  bufsRead[i]=(char *)malloc(sizeof(char )*MAX);
			  }
			  if(bufsWrite[i]!=NULL)
			  {
				  bufsWrite[i]=(char *)malloc(sizeof(char )*MAX);
			  }
		  }*/
		  printf("connected from client %d\n",conns[0]);
	  }
	  else
	  {
		  outerr("accept return error,continue");
		  continue;
	  }

	  while(1)
	  {
          FD_ZERO(&rds);
          FD_ZERO(&wts);

	  FD_SET(0,&rds);
	  FD_SET(1,&wts);
	  maxfd=1;

	  FD_SET(sockfd,&rds);
	  if(sockfd>maxfd)
		  maxfd=sockfd;


	  tv.tv_sec=1;
	  tv.tv_usec=10;


	  for(int i=0;i<curConnNum;i++)
		 {
			 FD_SET(conns[i],&rds);
			 FD_SET(conns[i],&wts);
			 if(conns[i]>maxfd)
				 maxfd=conns[i];
		 }



	  ret=select(maxfd+1,&rds,&wts,NULL,&tv);

	  //printf("ret=%d\n",ret);
/*	  if(ret==-1)
	  {
		  outerr("select return error");
		  break;
	  }
	  else if (ret==0)
	  {
		//  outerr("select return 0, no data ready,continue");
		  continue;
	  }
	  */
	  if(ret>0)
	  {

		  for(int i=0;i<curConnNum;i++)
		  {
			  if(FD_ISSET(conns[i],&rds))
			  {
				  receiveData(i);
			  }
			  if(FD_ISSET(conns[i],&wts))
			  {
				  if(strlen(bufsWrite[i])>0)
					  sendData(i);
			  }
		  }

		  if(FD_ISSET(sockfd,&rds))
		  {

			  conns[curConnNum]=accept(sockfd,NULL,NULL);
			 // memset(bufsRead[curConnNum],0,MAX);
			  //memset(bufsWrite[curConnNum],0,MAX);
			  if(conns[curConnNum]>0)
			  {
				  //if(bufsRead[curConnNum]!=NULL)
				  {
					  bufsRead[curConnNum]=(char *)malloc(sizeof(char )*MAX);
				  }
				  //if(bufsWrite[curConnNum]!=NULL)
				  {
					  bufsWrite[curConnNum]=(char *)malloc(sizeof(char )*MAX);
				  }
				  curConnNum++;
				  printf("a new client connected\n");
			  }
		  }
	  }
	  	

	  }
     }
     close(sockfd);
}

