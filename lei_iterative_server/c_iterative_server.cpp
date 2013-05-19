
#include"c_iterative_server.h"

/********************************************************************************************/
/********************************************************************************************/
NetAddress::NetAddress()
{
	p=-1;
	SAserverAddr=0;
	host=0;
}

NetAddress::NetAddress(const char * h, int p)
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

Socket::close()
{
	if(sockfd!=0)
		close(sockfd);
}

Socket::setOption()
{}

Socket::getOption()
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

Server::acceptor()
{

}

/********************************************************************************************/
/********************************************************************************************/
Iterative_Server::init()
{
	NetAddress *na=new NetAddress(host,port);
	Socket * sock=new Socket();
        bind(sock->sockfd,na->SAserverAddr,sizeof(sa->serverAddr));
	listen(sock->sockfd,LISTENQUE);
	return sock->sockfd;
}



Iterative_Server::handleConnection()
{

	return 0;
}

Iterative_Server::handleData()
{
	return 0;
}

Iterative_Server::run()
{
	int retsock;
	if( (retsock=init())<=0)
	{
		outerr("server init error, exit");
		exit(0);
	}

	fprintf(stdout, "the server run:\n");

	
	SocketStream *ss;
	for(;;)
	{

		ss=acceptor(retsock);
		if(waitfor_multievent()==-1)
			return -1;
		if(handleConnection()==-1)
			return -1;
		if(handleData()==-1)
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





