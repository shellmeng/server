
#include"c_thread_server.h"
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
int handleData(int conn, char * buf)
{
	sendData(conn, buf);
	return 1;
			
}
/* 
receive data from socket conns[clientNum], and the data are stored in the bufsRead[clientNum] 
return 1 if everything is ok
return -1 is there is somethign wrong ,but wouldn't exit
 */
void* receiveData(void *tapara)
{

  ThreadArgs * ta=(ThreadArgs *)tapara;
  int ret;
  int n;

  if( ta->buf==NULL)
  {
	  outerr("bufsRead no space");
	  exit(0);
  }
  memset(ta->buf,0,strlen(ta->buf));
  printf("here read\n");
  n=read(ta->conn,ta->buf,MAX-1);
  if(n>0)
  {
	  ta->buf[n]=0;
	  puts(ta->buf);
	  ret=handleData(ta->conn,ta->buf);
	  if(ret!=1)
	  {
		  outerr("error in hanleData");
		  exit(0);
	  }
	  return 0;
  }
  else
  {

	 // outerr("the receive didnot received data");
	  return 0;
  }
}

int sendData(int conn, char * bufsRead)
{
	printf("in sendData\n");
	int n=0;
	char * start=bufsRead;
	if(strlen(start)>0)
		//n=write(conns[clientNum],bufWrite[clientNum],strlen(bufWrite[clientNum];
	{
		printf("the data in bufs is to send \n");
		puts(start);
		n=write(conn,start,strlen(start));
		if(n==strlen(bufsRead) )
		{
			printf("yes, all sended\n");
			return 0;
		}
		else if(n>0 &&n<strlen(start))
		{
			start+=n;
			memcpy(bufsRead,start,strlen(start));
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

int threadHandle(int sockfd)
{

	pthread_attr_t tattr;
	pthread_t dealClient;
	void * status;
	void *args;
	int ret;

	ThreadArgs ta;


	int conn=0;
	char bufsRead[MAX];
	memset(bufsRead,0,MAX);
	conn=accept(sockfd,NULL,NULL);
	if(conn<=0)
	{
		outerr("error from accept\n");
		exit(0);
	}

	ta.conn=conn;
	ta.buf=bufsRead;

	ret=pthread_create(&dealClient,NULL,receiveData,(void *) &ta);
	printf("in thread %d\n",dealClient);
	if(ret!=0)
	{
		outerr("create thread failed");
		exit(0);
	}

	pthread_join(dealClient,&status);
	return 0;
}
