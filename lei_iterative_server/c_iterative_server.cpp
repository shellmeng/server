
#include"c_iterative_server.h"

/********************************************************************************************/
/********************************************************************************************/
NetAddress::NetAddress()
{
	port=-1;
	SAserverAddr=0;
	host=0;
}

NetAddress::NetAddress(char * h, int p)
{

     port =p;
     host=h;
     bzero(&serverAddr,sizeof(serverAddr));

     serverAddr.sin_family=AF_INET;
     serverAddr.sin_port=htons(p);
     serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    
     SAserverAddr=(struct sockaddr*)&serverAddr,sizeof(serverAddr);
}

int NetAddress::stringToAddr()
{}
int NetAddress::addrToString()
{}
int NetAddress::getPort()
{
	if(port>0)
		return port;
	else
	{
		fprintf(stdout,"the port is illegal,exit\n");
		exit(0);
	}
}
/********************************************************************************************/
/********************************************************************************************/


/********************************************************************************************/
/********************************************************************************************/

Socket::Socket()
{
     if ((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
     {
          outerr("new socket error in server\n");
          exit(-1);
     }

}

int Socket::sclose()
{
	if(sockfd!=0)
		close(sockfd);
}

int Socket::setOption()
{}

char * Socket::getOption()
{}
/********************************************************************************************/
/********************************************************************************************/



Server::Server()
{
	fprintf(stdout,"construct a server base\n");
	port=12346;
	host=0;

}

Server::Server(char * seraddr, int pt)
{
	fprintf(stdout,"construct a server base\n");
	port=pt;
	host=seraddr;
}

int Server::acceptor(int sock, SocketStream & ss)
{

	int conn =accept(sock, NULL, NULL);
	ss.sockfd=conn;
	
	//accept();
}

/********************************************************************************************/
/********************************************************************************************/

SocketStream::SocketStream():Socket()
{

	readbuf=0;
	sendbuf=0;
	readbuf =(char *) malloc( sizeof(char) * MAX);
	sendbuf =(char *) malloc( sizeof(char) * MAX);
	if(readbuf==0 || sendbuf==0)
	{

		outerr("malloc for buf error");
		exit(0);
	}
}
int SocketStream::recv()
{

	int n;
	n=read(sockfd,readbuf,MAX);
	if(n>0)
	{
		readbuf[n]=0;
		printf("read success\n");
		return 1;
	}
	else
		return 0;
		
}
int SocketStream::send()
{

	if(sendbuf!=0)
		write(sockfd, sendbuf, strlen(sendbuf));

	printf("write success\n");
}
/********************************************************************************************/
/********************************************************************************************/
int Iterative_Server::init()
{
	NetAddress *na=new NetAddress(host,port);
	Socket * sock=new Socket();
        bind(sock->sockfd,na->SAserverAddr,sizeof(na->serverAddr));
	listen(sock->sockfd,LISTENQUE);
	return sock->sockfd;
}



int Iterative_Server::handleConnection()
{

	return 0;
}

int Iterative_Server::handleData( SocketStream & ss)
{

	ss.recv();
	if(strlen(ss.readbuf)>0)
	{
		memcpy(ss.sendbuf, ss.readbuf,strlen(ss.readbuf));
		ss.readbuf[0]=0;
	}

	ss.send();
	ss.sclose();
	return 0;
}

int Iterative_Server::waitfor_multievent()
{}
int Iterative_Server::run()
{
	int retsock;
	if( (retsock=init())<=0)
	{
		outerr("server init error, exit");
		exit(0);
	}

	fprintf(stdout, "the server run:\n");

	
	SocketStream ss;
	for(;;)
	{

		acceptor(retsock,ss);
		if(waitfor_multievent()==-1)
			return -1;
		if(handleConnection()==-1)
			return -1;
		if(handleData(ss)==-1)
			return -1;
	}




}

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
     listen(sockfd,LISTENQUE);

     return sockfd;

}

int echo(int conn)
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





