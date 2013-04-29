#include"c_asyn_server.h"
int main()
{

     printf("start server\n");
     int sockfd,connfd,n;

     sockfd=buildConnection(PORT);

     doselect(sockfd);
}
