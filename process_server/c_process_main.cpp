#include"c_process_server.h"

int sockfd;
void exit_app(int sockfd)
{
	if(sockfd>0)
		close(sockfd);
	exit(0);
}
int main()
{

     printf("start server\n");
     int connfd,n;

     signal(SIGINT,exit_app);
     sockfd=buildConnection(PORT);

     while(1)
     {
	     processHandle(sockfd);
     }
}
