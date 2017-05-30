/*****************************************************************************
 * FILE NAME：
 *      main.c
 * DESCRIPTION:
 *      服务器端的函数入口和主程序
 * AUTHOR:
 *      Michael Xu (xuchuaner@qq.com)
 * CREATED DATE:
 *      2017.05.09
 * MODIFICATION HISTORY:
 * --------------------------------------
 *      2017-05-30 00:03:44 基本实现多线程功能，但是具体的客户请求处理的核心函数
 *      serverWork需要具体完善
 *      2017-05-30 11:37:07 serverWork 函数实现获取客户端的 ip信息
*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#include <unistd.h> //read,write
#include <sys/socket.h> //socket相关函数
#include <netinet/in.h> //socket结构体
#include <fcntl.h>
#include <pthread.h>    //pthread
#include <arpa/inet.h>  //网络/本地地址转换
#include <sys/types.h>  //设置套接字属性 setsockopt


#include "mim_sc_common.h"
#include "mim_server_db.h"
#include "mim_server_client_request.h"
#include "server_socket.h"

/* 全局变量，因为本程序只使用一个数据库对象 */
sqlite3 *sqlHdl = NULL; //SQL处理对象指针
sqlite3** pSqlHdl = &sqlHdl;    //二级指针

/*****************************************************************************
 * DECRIPTION:
 *      serverWork() 新客户端连接后的核心处理函数
 *      负责处理用户请求
 * INPUTS:
 *      int* connfd  连接的客户端socket描述符 *connfd
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
void serverWork(int* connfd)
{
    ssize_t realRead, realWrite;    //实际接收到的和发送的数据大小
    char buf[BUF_SIZE] = {'\0'};    //暂存接收和发送的数据buf
    SAIN clientAddr;
    int clientAddrLen = sizeof(clientAddr);

    bzero((void*)&clientAddr, clientAddrLen);
    getpeername (*connfd, (SA*)&clientAddr, (socklen_t*)&clientAddrLen);

#ifdef _DEBUG
    PRINTF("In a new thread = %lu.", pthread_self ());
    PRINTF("New connection. connfd = %d. IP: %s:%d",
           *connfd,
           inet_ntoa(clientAddr.sin_addr),
           ntohs(clientAddr.sin_port));
#endif

    return ;
}

/*****************************************************************************
 * DECRIPTION:
 *      main 函数  程序入口
 * FUNCTIONS:
 *      1. 数据库的初始化；
 *      2. 套接字的建立
 *      3. 多线程的建立
 * 具体的客户端连接后的处理操作全部放在 serverWork() 函数中
*****************************************************************************/
int main()
{
    STATUS ret = ERROR;

    PRINTF("-------------------------------------\n"
           "MIM SERVER INITIALIZING...\n"
           "-------------------------------------\n");

    /* 打开数据库 */
    ret = sqlite3_open (DB_FILE, &sqlHdl);
    if (SQLITE_OK == ret)
    {
        PRINTF("[DB open ok.]");
    }
    else
    {
        PRINTF("[DB open failed.]");
        EXIT(EXIT_FAILURE);
    }

    /* 初始化数据库即相关表 */
    ret = sDbInit(sqlHdl);
    if (OK == ret)
    {
        PRINTF("DB:%s Init OK.", DB_FILE);
        PRINTF("-------------------------------------\n"
               "MIM SERVER INITIALIZATION COMPLETED!\n"
               "-------------------------------------\n");
    }
    else
    {
        PRINTF("DB:%s Init ERROR.", DB_FILE);
        PRINTF("-------------------------------------\n"
               "MIM SERVER INITIALIZATION FAILED!\n"
               "-------------------------------------\n");
        EXIT(EXIT_FAILURE);
    }

    /************test**************/
    /************test**************/

    /* 主进程 */
    SAIN servAddr, clientAddr;  //定义服务器和客户端的地址结构体
    int listenfd, connfd;   //监听、连接套接字
    int clientAddrLen = sizeof(clientAddr);  //客户端socket地址大小

    /* 1. 创建套接字 */
    listenfd = socketCreate (AF_INET, SOCK_STREAM, 0); //创建监听套接字,tcp,可reuse

    /* 创建监听的地址 */
    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;  //采取TCP协议
    servAddr.sin_port = htons(SERVER_PORT); //指定端口2017
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //系统自动获取本机的IP地址

    /* 2. 绑定到套接字 */
    socketBind (listenfd, (const SA*)&servAddr, sizeof(servAddr));

    /* 3.监听 */
    socketListen (listenfd, BACKLOG);

    while(1)
    {
        PRINTF("======waiting for client's request======\n");
        pthread_t newThread;

        //阻塞，知道服务器接收到一个新的 connect 请求
        connfd = socketAccept (listenfd, NULL, NULL);
        if(connfd < -1)
        {
            continue;   //继续loop， 知道有connect
        }

        /* 当有新的用户连接后 */
        // 1.获取客户端的IP信息
        bzero((void*)&clientAddr, clientAddrLen);
        getpeername (connfd, (SA*)&clientAddr, (socklen_t*)&clientAddrLen);

#ifdef _DEBUG
        PRINTF("Got a New connection. connfd = %d. IP: %s:%d",
               connfd,
               inet_ntoa(clientAddr.sin_addr),
               ntohs(clientAddr.sin_port));
#endif
        //2.创建新的线程为其进行服务
        if(-1 == pthread_create(&newThread, NULL, (void*)(&serverWork), &connfd))
        {
            PRINTF("New Thread Created Failed.");
        }
    }//end of while

    if ( -1 != socketShutdown (listenfd, SHUT_RDWR))
    {
        PRINTF("[socket shutdown...]");
    }


    /* 关闭数据库 */
    sDbClose (sqlHdl);
    PRINTF ("\n");

    return 0;
}
