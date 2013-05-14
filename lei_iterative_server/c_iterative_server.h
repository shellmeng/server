
#ifndef C_ITERATIVE_SERVER_H
#define  C_ITERATIVE_SERVER_H
#include"netHeader.h"

#define MAX 1023
#define LISTENQUE 10
#define PORT 12346

class Server
{
	public:
		Server();
		Server(char * serveraddr, int port );
		virtual void run()=0;
		virtual void init()=0;
		virtual handleConnection()=0;
		virtual handleData()=0;
	private:
		char * serverAddr;
		int port;
};
class Iterative_Server:public Server
{
	public:

};

int buildConnection(int port);

int echo(int conn);
#endif
