/*****************************************************************************
 * FILE NAME：
 *      mim_server_db.c
 * DESCRIPTION:
 *      实现服务器端（DB模块）一些常用的函数功能
 * AUTHOR:
 *      Michael Xu (xuchuaner@qq.com)
 * CREATED DATE:
 *      2017.05.13 14:42
 * MODIFICATION HISTORY:
 * --------------------------------------
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <errno.h>
#include <string.h>

#include "mim_sc_common.h"
#include "mim_server_db.h"

/*****************************************************************************
 * DECRIPTION:
 *      检验SQL函数执行结果
 * INPUTS:
 *      sqlite3* sqlHdl --  SQL处理对象
 *      STATUS ret --  相应的SQL函数返回值
 *      char* curOpera --   当前执行的操作名字
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      NONE
 * CAUTIONS:
 *      NONE
*****************************************************************************/
void sSqlChkRet(sqlite3* sqlHdl, STATUS ret, char* curOpera)
{
    /* 如果返回值不是OK,则输出返回值和警告信息 */
    if (ret != SQLITE_OK)
    {
        PRINTF("PRINTF:ret = %d.", ret);
        fprintf(stderr, "\nSQL error(%s): %s",
                curOpera, sqlite3_errmsg(sqlHdl));
        fflush(stderr);
#ifdef _STRICT_DEBUG
        EXIT(EXIT_FAILURE);
#endif
    }
    else
    {
#ifdef _DEBUG
        PRINTF("SQL ok(%s).", curOpera);
#endif
    }
    return ;
}

/*****************************************************************************
 * DECRIPTION:
 *      数据库的创建或打开操作,将打开的数据库操作对象输出到sqlHdl
 * INPUTS:
 *      数据库文件名 dbFileName
 * OUTPUTS:
 *      打开的数据库操作对象 sqlite3 **sqlHdl
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      如果不在当前文件夹下创建数据库，需要提供完整
 *      路径，最好使用绝对路径
*****************************************************************************/
STATUS sDbOpen(const char *dbFileName, sqlite3 **sqlHdl)
{
    STATUS ret = SQLITE_ERROR;

    ret = sqlite3_open (dbFileName, sqlHdl);
    sSqlChkRet (*sqlHdl, ret, "Open DB");

    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      数据库的关闭操作
 * INPUTS:
 *      数据库操作对象 sqlite3* sqlHdl
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
STATUS sDbClose(sqlite3 *sqlHdl)
{
    STATUS ret = ERROR;

    ret = sqlite3_close(sqlHdl);
    sSqlChkRet (sqlHdl, ret, "Close DB");
    PRINTF ("\n");
    return ret;
}
