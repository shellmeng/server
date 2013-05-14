
#include"c_iterative_server.h"

Server::Server()
{
	printf("construct the virtual Server\n");
}

Server::Server(char * serveraddr, int pt)
{
	printf("construct the virtual Server\n");
	if(serveraddr!=NULL)
		serverAddr=serveraddr;
	port=pt;
}

Iterative_Server::init()
{}

Iterative_Server::handleConnection()
{}

Iterative_Server::handleData()
{}

Iterative_Server::run()
{}

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





