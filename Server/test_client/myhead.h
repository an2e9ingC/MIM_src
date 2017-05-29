/*************************************************************************
> File Name: myhead.h
> Author: Michael Jay
> mail: xuchuanwork@foxmail.com
> Created Time: 2016年07月07日 星期四 19时22分09秒
> Function: 
	1.常见的头文件
	2.常见函数重定义
	3.网络编程结构体重命名
 ************************************************************************/

#ifndef _MYHEAD_H
#define _MYHEAD_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>

typedef struct sockaddr		SA;
typedef struct sockaddr_in SAIN;

int Socket(int domain, int type, int protocol)
{
	int ret;
	ret = socket(domain, type, protocol);
	if(ret < 0)
	{
		perror("socket");
		exit(EXIT_FAILURE);
	}
	return ret;
}

int Bind(int sockfd, const SA *addr, socklen_t addrlen)
{
	int ret;
	ret = bind(sockfd, addr, addrlen);
	if(ret < 0)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	return ret;
}

int Listen(int sockfd, int backlog)
{
	int ret;
	ret = listen(sockfd, backlog);
	if(ret < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	return ret;
}

int Accept(int sockfd, SA *addr, socklen_t *len)
{
	int ret;
	ret = accept(sockfd, addr, len);
	if(ret < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	return ret;
}

int Recv(int sockfd, void *buf, size_t len, int flags)
{
	int ret;
	ret = recv(sockfd, buf, len, flags);
	if(ret < 0)
	{
		perror("recv");
		exit(EXIT_FAILURE);
	}
	return ret;
}

int Recvfrom(int sockfd, void *buf, size_t len, int flags, SA* src_addr, socklen_t *addrlen)
{
	int ret;
	ret = recvfrom(sockfd, buf, len, flags, src_addr, addrlen);
	if(ret < 0)
	{
		perror("recvfrom");
		exit(EXIT_FAILURE);
	}
	return ret;
}

int Connect(int sockfd, SA* addr, socklen_t addrlen)
{
	int ret;
	ret = connect(sockfd, addr, addrlen);
	if(ret < 0)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	return ret;
}

int Fork(void)
{
	int ret = fork();
	if(ret < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	return ret;
}

ssize_t Send(int sockfd, const void* buf, size_t len, int flag)
{
	int ret = send(sockfd, buf, len, flag);
	if(ret < 0)
	{
		perror("send");
		exit(EXIT_FAILURE);
	}

	return ret;
}

int Close( int fd)
{
	int ret = close(fd);
	if(ret < 0)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
	return ret;
}

int Shutdown(int sockfd, int how)
{
	int ret = shutdown(sockfd, how);
	if(ret < 0)
	{
		perror("shutdown");
		exit(EXIT_FAILURE);
	}
	return ret;
}


#endif
