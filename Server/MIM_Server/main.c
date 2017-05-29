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
 *
*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <pthread.h>

#include "mim_sc_common.h"
#include "mim_server_db.h"
#include "mim_server_client_request.h"
#include "server_socket.h"

/* 全局变量，因为本程序只使用一个数据库对象 */
sqlite3 *sqlHdl = NULL; //SQL处理对象指针
sqlite3** pSqlHdl = &sqlHdl;    //二级指针

void newThreadWork(void)
{
    PRINTF("this is a new thread = %lu.", pthread_self ());
    return ;
}

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
    ssize_t realRead, realWrite;    //实际接收到的和发送的数据大小
    char buf[BUF_SIZE] = {'\0'};    //暂存接收和发送的数据buf

    /* 1. 创建套接字 */
    listenfd = socketCreate (AF_INET, SOCK_STREAM, 0);   //创建监听套接字,tcp,流式

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
        printf("======waiting for client's request======\n");
        pthread_t newThread;

        //阻塞，知道服务器接收到一个新的 connect 请求
        connfd = socketAccept (listenfd, (SA*)&servAddr, (socklen_t*)&clientAddrLen);
        if(connfd < -1)
        {
            continue;   //继续loop， 知道有connect
        }

        //当有新的客户端连接后，创建新的线程进行服务
        PRINTF("Got a New connection. connfd = %d.", connfd);
        if(-1 == pthread_create(&newThread, NULL, (void*)(&newThreadWork), NULL))
        {
            PRINTF("New Thread Created Failed.");
        }


    }




    /* 关闭数据库 */
    sDbClose (sqlHdl);
    PRINTF ("\n");

    return 0;
}
