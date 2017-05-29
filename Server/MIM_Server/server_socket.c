/*****************************************************************************
 * FILE NAME：
 *      server_socket.c
 * DESCRIPTION:
 *      实现套接字相关的函数模块
 * AUTHOR:
 *      Michael Xu (xuchuaner@qq.com)
 * CREATED DATE:
 *      2017-05-29 21:04:18
 * MODIFICATION HISTORY:
 * --------------------------------------
 *
*****************************************************************************/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "server_socket.h"

/*****************************************************************************
 * DECRIPTION:
 *      SocketCreate() 根据参数创建套接字
 * INPUTS:
 *      int domain      //协议族 AF_INET
 *      int type        //socket类型  流式TCP
 *      int protocol    // 0自动匹配
*****************************************************************************/
int socketCreate(int domain, int type, int protocol)
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

/*****************************************************************************
 * DECRIPTION:
 *      socketBind() 把一个地址族中的特定地址赋给socket
 * INPUTS:
 *      int sockfd          socket描述符
 *      const SA *addr      地址
 *      socklen_t addrlen   地址的长度
*****************************************************************************/
STATUS socketBind(int sockfd, const SA *addr, socklen_t addrlen)
{
    STATUS ret;
    ret = bind(sockfd, addr, addrlen);
    if(ret < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      socketListen监听指定套接字，listen函数将socket变为被动类型的,等待客户的连接请求
 * INPUTS:
 *      sockfd      套接字
 *      backlog     相应socket可以排队的最大连接个数
*****************************************************************************/
STATUS socketListen(int sockfd, int backlog)
{
    STATUS ret = ERROR;
    ret = listen(sockfd, backlog);
    if(ret < 0)
    {
        perror("listen");
    }
    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      socketAccept 接收Client发出的connect请求
 * INPUTS:
 *      int sockfd      监听套接字
 *      SA *addr        连接的客户端socket地址
 *      socklen_t *len  地址大小
*****************************************************************************/
int socketAccept(int sockfd, SA *addr, socklen_t *len)
{
    int ret;
    ret = accept(sockfd, addr, len);
    if(ret < 0)
    {
        perror("accept");
    }
    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      socketRecv 接收套接字中的数据
 * INPUTS:
 *      sockfd
 *      buff：    存放要接收数据的缓冲区
 *      nbytes:   实际要接收到的数据的字节数
 *      flags：   一般设置为0
*****************************************************************************/
ssize_t socketRecv(int sockfd, void *buf, size_t len, int flags)
{
    ssize_t ret;
    ret = recv(sockfd, buf, len, flags);
    if(ret < 0)
    {
        perror("recv");
    }
    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      socketSend 发送数据
 * INPUTS:
 *      sockfd
 *      buff：    存放要发送数据的缓冲区
 *      nbytes:   实际要发送的数据的字节数
 *      flags：   一般设置为0
*****************************************************************************/
ssize_t socketSend(int sockfd, const void* buf, size_t len, int flag)
{
    int ret = send(sockfd, buf, len, flag);
    if(ret < 0)
    {
        perror("socket send");
    }

    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      CloseSocket()关闭指定套接字
 * INPUTS:
 *      sockfd
*****************************************************************************/
STATUS socketClose(int sockfd)
{
    STATUS ret = close(sockfd);
    if(ret < 0)
    {
        perror("socket close");
    }
    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      socketShutdown 关闭套接字所有的连接
 * INPUTS:
 *      sockfd
 *      how     如何shutdown
*****************************************************************************/
STATUS socketShutdown(int sockfd, int how)
{
    int ret = shutdown(sockfd, how);
    if(ret < 0)
    {
        perror("socket shutdown");
        exit(EXIT_FAILURE);
    }
    return ret;
}
