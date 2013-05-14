
#ifndef C_ITERATIVE_SERVER_H
#define  C_ITERATIVE_SERVER_H
#include"netHeader.h"

#define MAX 1023
#define LISTENQUE 10
#define PORT 12346

class NetAddress
{
	private:
		struct sockaddr_in serverAddr;
	public:
		NetAddress();
		NetAddress(const char * host,int port);
		int stringToAddr();
		int addrToString();
		int getPort();
		char * getHost();
		int set(const char * host, int port);
};

class Socket
{
	private:
		int sockfd;
	public:
		int open();
		int close();
		char * getRemoteAddr();
		char * getLocalAddr();
		int setOption();
		char * getOption();
};

class SocketStream:public Socket
{
	private:
	public:
		recv();
		send();
		recvn();
		sendn();
		recvvn();
		sendvn();
}

class SocketConnect:public Socket
{
	private:
		NetAddress na;
	public:
		int connect();
};

class SocketAcceptor:public Socket
{
	private:
		NetAddress netaddr;
		SocketStream sockstream;
	public:
		open(NetAddress * na);
		accept(SocketStream & ss);

};
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
		NetAddress  netaddr;
};
class Iterative_Server:public Server
{
	public:

};

int buildConnection(int port);

int echo(int conn);
#endif
