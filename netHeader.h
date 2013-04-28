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

#define PORT 12346
#define MAX 255

void outerr(char * loc)
{
	printf("%s",loc);
	printf("\n");

	printf("%s\n",strerror((int)error));
	
}

#endif

