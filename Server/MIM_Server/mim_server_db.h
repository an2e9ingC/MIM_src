/*****************************************************************************
 * FILE NAME：
 *      mim_server_db.h
 * DESCRIPTION:
 *      声明服务器端（DB模块）的常量和对外提供的借口
 * AUTHOR:
 *      Michael Xu (xuchuaner@qq.com)
 * CREATED DATE:
 *      2017.05.09-15:41
 * MODIFICATION HISTORY:
 * --------------------------------------
 *      2017-05-15 00:11:10 添加 sSqlChkRet 函数，处理SQL操作结果
 *      2017-05-15 01:26:06 设置 sSqlChkRet函数为static，并直接定义在mim_server_db.c
*****************************************************************************/

#ifndef MIM_SERVER_DB_H
#define MIM_SERVER_DB_H

#include <sqlite3.h>
#include "mim_sc_common.h"


/*****************************************************************************
 * DECRIPTION:
 *      数据库的创建或打开操作
 * INPUTS:
 *      数据库文件名 dbFileName
 * OUTPUTS:
 *      返回的数据库操作对象 sqlHdl
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      如果不在当前文件夹下创建数据库，需要提供完整
 *      路径，最好使用绝对路径
*********************************************/
STATUS sDbOpen(const char *dbFileName, sqlite3 **sqlHdl);

/***********************************************
 * DECRIPTION:
 *      数据库的关闭操作
 * INPUTS:
 *      数据库文件名 dbFileName
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      如果不在当前文件夹下创建数据库，需要提供完整
 *      路径，最好使用绝对路径
*****************************************************************************/
STATUS sDbClose(sqlite3 *sqlHdl);

#endif // MIM_SERVER_H
