
#ifndef C_ITERATIVE_SERVER_H
#define  C_ITERATIVE_SERVER_H
#include"netHeader.h"

#define MAX 1023
#define LISTENQUE 10
#define PORT 12346

/*****************************************************************************/
/*****************************************************************************/
class NetAddress
{
	//private:
	public:
		struct sockaddr_in serverAddr;
		int port;
		char * host;
	public:
		struct sockaddr *SAserverAddr;
		NetAddress();
		NetAddress(char * host,int port);
		int stringToAddr();
		int addrToString();
		int getPort();
		char * getHost();
	//	int set(const char * host, int port);
};
/*****************************************************************************/
/*****************************************************************************/
class Socket
{
	//protected:
	public:
		int sockfd;
	public:
		Socket();
		//int open();
		int sclose();
		//char * getRemoteAddr();
		//char * getLocalAddr();
		int setOption();
		char * getOption();
};

/*****************************************************************************/
/*****************************************************************************/
class SocketStream:public Socket
{
//	private:
	public:
		char * readbuf;
		char * sendbuf;
	public:
		SocketStream();
		int recv();
		int send();
		int recvn();
		int sendn();
		int recvvn();
		int sendvn();
};

/*****************************************************************************/
/*****************************************************************************/
/*class SocketConnect:public Socket
{
	private:
		NetAddress na;
	public:
		int connect();
};*/

/*****************************************************************************/
/*****************************************************************************/
/*class SocketAcceptor:public Socket
{
	private:
		//NetAddress netaddr;

	public:
		open(NetAddress * na);
		accept(SocketStream & ss);

};*/

/*****************************************************************************/
/*****************************************************************************/
class Server
{
	public:
		Server();  //default port
		Server(char * serveraddr, int port );
		virtual int  run()=0;
		virtual int  init()=0;
		virtual int handleConnection()=0;
		virtual int handleData(SocketStream & )=0;
		virtual int waitfor_multievent()=0;

	//protected:
	public:
		int port;
		char * host;
		int acceptor(int ,SocketStream &ss);
		//NetAddress  netaddr;
		//Socket sock;
};
/*****************************************************************************/
/*****************************************************************************/
class Iterative_Server:public Server
{

	public:

	 int  run();
	 int  init();
	 int handleConnection();
	 int handleData(SocketStream&);
	 int waitfor_multievent();
};

/*****************************************************************************/
/*****************************************************************************/
int buildConnection(int port);

int echo(int conn);
#endif
