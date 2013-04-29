
#ifndef C_ITERATIVE_SERVER_H
#define  C_ITERATIVE_SERVER_H
#include"netHeader.h"

#define MAX 10
#define LISTENQUE 10
#define PORT 12346
extern fd_set rds,wts,exps;

int buildConnection(int port);
int doselect(int s);

int echo(int conn);
#endif
