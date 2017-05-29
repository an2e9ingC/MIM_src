/*****************************************************************************
 * FILE NAME：
 *      server_socket.h
 * DESCRIPTION:
 *      socket相关功能
 * AUTHOR:
 *      Michael Xu (xuchuaner@qq.com)
 * CREATED DATE:
 *      2017-05-29 16:02:13
 * MODIFICATION HISTORY:
 * --------------------------------------
 *
*****************************************************************************/

#ifndef _SERVER_SOCKET_H
#define _SERVER_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>

#include "mim_sc_common.h"

#define  BACKLOG 10 //相应socket可以排队的最大连接个数
#define BUF_SIZE 1024   //保存接收和发送的buf的大小

typedef struct sockaddr	SA; //generic socket address通用套接字结构体
typedef struct sockaddr_in SAIN;   //定义互联网的套接字地址Internet socket address

/*****************************************************************************
 * DECRIPTION:
 *      socketCreate() 根据参数创建套接字
 * INPUTS:
 *      int domain      //协议族 AF_INET
 *      int type        //socket类型  流式TCP
 *      int protocol    // 0自动匹配
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      套接字描述符  --  成功
 *      直接结束进程   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
int socketCreate(int domain, int type, int protocol);

/*****************************************************************************
 * DECRIPTION:
 *      socketBind() 把一个地址族中的特定地址赋给socket
 * INPUTS:
 *      int sockfd          socket描述符
 *      const SA *addr      地址
 *      socklen_t addrlen   地址的长度
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      直接结束进程   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
int socketBind(int sockfd, const SA *addr, socklen_t addrlen);

/*****************************************************************************
 * DECRIPTION:
 *      socketListen 监听指定套接字，listen函数将socket变为被动类型的，等待客户的连接请求
 * INPUTS:
 *      sockfd      套接字
 *      backlog     相应socket可以排队的最大连接个数
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS socketListen(int sockfd, int backlog);

/*****************************************************************************
 * DECRIPTION:
 *      socketAccept 接收Client发出的connect请求
 * INPUTS:
 *      int sockfd      监听套接字
 *      SA *addr        连接的客户端socket地址
 *      socklen_t *len  地址大小
 * OUTPUTS:
 *      *addr, *len
 * RETURNS:
 *      成功  --   返回与客户端通信新socket,说明已经与客户端建立连接
 *      ERROR   --  失败
 * CAUTIONS:
 *      accept默认会阻塞进程，直到有一个客户连接建立后返回，返回一个新可用的套接字(connfd)
 *      如果需要非阻塞，需要调用fcntl来修改套接字描述符的属性
*****************************************************************************/
int socketAccept(int sockfd, SA *addr, socklen_t *len);

/*****************************************************************************
 * DECRIPTION:
 *      socketRecv 接收套接字中的数据
 * INPUTS:
 *      sockfd
 *      buff：    存放要接收数据的缓冲区
 *      nbytes:   实际要接收到的数据的字节数
 *      flags：   一般设置为0
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      接收到的数据大小  --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
ssize_t socketRecv(int sockfd, void *buf, size_t len, int flags);

/*****************************************************************************
 * DECRIPTION:
 *      socketSend 发送数据
 * INPUTS:
 *      sockfd
 *      buff：    存放要发送数据的缓冲区
 *      nbytes:   实际要发送的数据的字节数
 *      flags：   一般设置为0
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      发送的数据大小  --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
ssize_t socketSend(int sockfd, const void* buf, size_t len, int flag);

/*****************************************************************************
 * DECRIPTION:
 *      socketClose()关闭指定套接字
 * INPUTS:
 *      sockfd
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS socketClose(int sockfd);

/*****************************************************************************
 * DECRIPTION:
 *      socketShutdown 关闭套接字所有的连接
 * INPUTS:
 *      socket
 *      how: SHUT_RD   = No more receptions;
 *           SHUT_WR   = No more transmissions;
 *           SHUT_RDWR = No more receptions or transmissions.
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS socketShutdown(int sockfd, int how);

#endif
