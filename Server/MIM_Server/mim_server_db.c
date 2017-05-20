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
 *      2017-05-15 01:27:32 添加 sSqlChkRet 函数，并设置为static模式
 *      2017-05-15 11:23:31 sSqlChkRet 对外提供
 *      2017-05-15 12:21:20 添加数据库（表）的初始化函数
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
 *      初始化用户密码表 USER_PASSWD_TBL
 * INPUTS:
 *      sqlite3* sqlHdl 数据库操作对象
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      static
*****************************************************************************/
static STATUS sTblUserPasswdInit(sqlite3* sqlHdl)
{
    STATUS ret = ERROR;
    const char *sql = "CREATE TABLE USER_PASSWD_TBL(\n"\
                "UID    INT     PRIMARY KEY     NOT NULL,\n"\
                "UNAME  TEXT    KEY             NOT NULL,\n"\
                "UPASSWD    TEXT                NOT NULL\n"\
                ");";
    PRINTF("%s", sql);
    ret = sqlite3_exec (sqlHdl, sql, 0, 0, 0);
    sSqlChkRet (sqlHdl, ret, "Init UserPasswd Tbl");

    if (SQLITE_OK == ret)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

/*****************************************************************************
 * DECRIPTION:
 *      初始化用户基本信息表 USER_INFO_TBL;
 * INPUTS:
 *      sqlite3* sqlHdl 数据库操作对象
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      static
*****************************************************************************/
static STATUS sTblUserInfoInit(sqlite3* sqlHdl)
{
    STATUS ret = ERROR;
    char *sql = "CREATE TABLE USER_INFO_TBL("
                "UID    INT     PRIMARY KEY     NOT NULL,\n"
                "SEX    TEXT    KEY             NOT NULL,\n"
                "EMAIL  TEXT,   \n"
                "TEL    TEXT    \n"
                ");";
    ret = sqlite3_exec (sqlHdl, sql, 0, 0, 0);
    sSqlChkRet (sqlHdl, ret, "Init UserInfo Tbl");

    if (SQLITE_OK == ret)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

/*****************************************************************************
 * DECRIPTION:
 *      初始化用户好友列表 USER_FRDS_TBL;
 * INPUTS:
 *      sqlite3* sqlHdl 数据库操作对象
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      static
*****************************************************************************/
static STATUS sTblUserFrdsInit(sqlite3* sqlHdl)
{
    STATUS ret = ERROR;
    char *sql = "CREATE TABLE USER_FRDS_TBL("
                "UID    INT     PRIMARY KEY     NOT NULL,\n"
                "FID    INT                     NOT NULL,\n"
                "REMARK  TEXT   \n"
                ");";
    ret = sqlite3_exec (sqlHdl, sql, 0, 0, 0);
    sSqlChkRet (sqlHdl, ret, "Init UserFrds Tbl");

    if (SQLITE_OK == ret)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

/*****************************************************************************
 * DECRIPTION:
 *      初始化用户在线状态信息表 USER_STAT_TBL;
 * INPUTS:
 *      sqlite3* sqlHdl 数据库操作对象
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      static
*****************************************************************************/
static STATUS sTblUserStatInit(sqlite3* sqlHdl)
{
    STATUS ret = ERROR;
    char *sql = "CREATE TABLE USER_STAT_TBL("
                "UID    INT     PRIMARY KEY     NOT NULL,\n"
                "STAT   TEXT                    NOT NULL,\n"
                ");";
    ret = sqlite3_exec (sqlHdl, sql, 0, 0, 0);
    sSqlChkRet (sqlHdl, ret, "Init UserStat Tbl");

    if (SQLITE_OK == ret)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

/*****************************************************************************
 * DECRIPTION:
 *      初始化 用户密码重置验证问题表 USER_VERIFY_TBL;
 * INPUTS:
 *      sqlite3* sqlHdl 数据库操作对象
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      static
*****************************************************************************/
static STATUS sTblUserVerifyInit(sqlite3* sqlHdl)
{
    STATUS ret = ERROR;
    char *sql = "CREATE TABLE USER_VERIFY_TBL("
                "UID    INT     PRIMARY KEY     NOT NULL,\n"
                "Q1     TEXT                    NOT NULL,\n"
                "Q2     TEXT                    NOT NULL,\n"
                "Q3     TEXT                    NOT NULL,\n"
                ");";
    ret = sqlite3_exec (sqlHdl, sql, 0, 0, 0);
    sSqlChkRet (sqlHdl, ret, "Init UserVerify Tbl");

    if (SQLITE_OK == ret)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}


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
 *      OK (0)       //处理成功
 *      ERROR (-1)    //处理失败
 * CAUTIONS:
*****************************************************************************/
STATUS sSqlChkRet(sqlite3* sqlHdl, STATUS ret, char* curOpera)
{
    STATUS stat = ERROR;
    /* 如果返回值不是OK,则输出返回值和警告信息 */
    if (ret != SQLITE_OK)
    {
        PRINTF("PRINTF:ret = %d.", ret);
        fprintf(stderr, "\nSQL error(%s): %s",
                curOpera, sqlite3_errmsg(sqlHdl));
        fflush(stderr);

        if (ret == SQLITE_BUSY)
        {
            return stat;    //如果是由于数据库繁忙直接返回
        }
        else
        {
    #ifdef _STRICT_DEBUG
            EXIT(EXIT_FAILURE); //如果是由于其他原因，结束进程
    #endif
        }//end of IF BUSY
    }
    else
    {
#ifdef _DEBUG
        PRINTF("SQL ok(%s).", curOpera);
#endif
        stat = OK;
    }//end of IF NOT OK

    return stat;
}

/*****************************************************************************
 * DECRIPTION:
 *      数据库的创建或打开操作,将打开的数据库操作对象输出到sqlHdl
 * INPUTS:
 *      数据库文件名 dbFileName
 * OUTPUTS:
 *      打开的数据库操作对象 sqlite3 *sqlHdl
 * RETURNS:
 *      NONE
 * CAUTIONS:
 *      如果不在当前文件夹下创建数据库，需要提供完整
 *      路径，最好使用绝对路径
*****************************************************************************/
STATUS sDbOpen(const char *dbFileName, sqlite3 *sqlHdl)
{
    STATUS ret = SQLITE_ERROR;

    ret = sqlite3_open (dbFileName, &sqlHdl);

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

/*****************************************************************************
 * DECRIPTION:
 *      sDbInit()   初始化数据库：初始化所有表
 * INPUTS:
 *      sqlite3* sqlHdl;    数据库操作对象
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbInit(sqlite3* sqlHdl)
{
    STATUS ret = ERROR;

    /* 初始化 用户名密码表 */
    ret = sTblUserPasswdInit(sqlHdl);
    if (ERROR == ret)
    {
        goto o_exit;
    }

    /* 初始化 用户信息表 */
    ret = sTblUserInfoInit (sqlHdl);
    if (ERROR == ret)
    {
        goto o_exit;
    }

    /* 初始化用户好友列表 */
    ret = sTblUserFrdsInit (sqlHdl);
    if (ERROR == ret)
    {
        goto o_exit;
    }

    /* 初始化用户在线状态信息表 */
    ret = sTblUserStatInit (sqlHdl);
    if (ERROR == ret)
    {
        goto o_exit;
    }

    /* 初始化 用户密码重置验证问题表 */
    ret = sTblUserVerifyInit (sqlHdl);
    if (ERROR == ret)
    {
        goto o_exit;
    }
o_exit:
    return ret;
}
