#ifndef NETHEADER_H
#define NETHEADER_H
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<error.h>
#include<unistd.h>
#include<sys/time.h>
#include<signal.h>
#include<pthread.h>





void outerr(char * loc);

typedef struct ThreadArgs
{
	int conn;
	char * buf;
};

#endif

