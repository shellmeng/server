#ifndef C_ITERATIVE_CLIENT_H
#define C_ITERATIVE_CLIENT_H
#include"netHeader.h"

#define MAX 1023
#define PORT 12346
/*
主要功能是创建一个到服务器的链接
参数是 ip 和 端口，char* 和int的
返回一个大于0的套接字，如果小于0，表示失败。会输出错误信息
*/
int buildConnection(char * addr,int port);


int clientReadWrite(int skn);

#endif
