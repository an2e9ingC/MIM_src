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
 *      2017-05-22 11:36:51 删除sDbOpen, 设置sDbClose返回值为void
 *      2017-05-22 15:31:43 精简.c文件中的函数注释
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
 * CAUTIONS:
 *      static
*****************************************************************************/
static STATUS sTblUserPasswdInit(sqlite3* sqlHdl)
{
    STATUS ret = ERROR;
    const char *sql = "CREATE TABLE USER_PASSWD_TBL(\n"\
                "UID    INT     PRIMARY KEY     NOT NULL,\n"\
                "UNAME  TEXT                     NOT NULL,\n"\
                "UPASSWD    TEXT                NOT NULL\n"\
                ");";

    ret = sqlite3_exec (sqlHdl, sql, 0, 0, 0);

#ifdef _DEBUG

    PRINTF("%s", sql);
    sSqlChkRet (sqlHdl, ret, __FUNCTION__);
#endif

    return ((SQLITE_OK == ret) ? OK : ERROR);
}

/*****************************************************************************
 * DECRIPTION:
 *      初始化用户基本信息表 USER_INFO_TBL;
 * INPUTS:
 *      sqlite3* sqlHdl 数据库操作对象
 * CAUTIONS:
 *      static
*****************************************************************************/
static STATUS sTblUserInfoInit(sqlite3* sqlHdl)
{
    STATUS ret = ERROR;
    char *sql = "CREATE TABLE USER_INFO_TBL("
                "UID    INT     PRIMARY KEY     NOT NULL,\n"
                "SEX    TEXT                    NOT NULL,\n"
                "EMAIL  TEXT,   \n"
                "TEL    TEXT    \n"
                ");";
    ret = sqlite3_exec (sqlHdl, sql, 0, 0, 0);

#ifdef _DEBUG
    PRINTF("%s", sql);
    sSqlChkRet (sqlHdl, ret, __FUNCTION__);
#endif

    return ((SQLITE_OK == ret) ? OK : ERROR);
}

/*****************************************************************************
 * DECRIPTION:
 *      初始化用户好友列表 USER_FRDS_TBL;
 * INPUTS:
 *      sqlite3* sqlHdl 数据库操作对象
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

#ifdef _DEBUG
    PRINTF("%s", sql);
    sSqlChkRet (sqlHdl, ret, __FUNCTION__);
#endif

    return ((SQLITE_OK == ret) ? OK : ERROR);
}

/*****************************************************************************
 * DECRIPTION:
 *      初始化用户在线状态信息表 USER_STAT_TBL;
 * INPUTS:
 *      sqlite3* sqlHdl 数据库操作对象
 * CAUTIONS:
 *      static
*****************************************************************************/
static STATUS sTblUserStatInit(sqlite3* sqlHdl)
{
    STATUS ret = ERROR;
    char *sql = "CREATE TABLE USER_STAT_TBL("
                "UID    INT     PRIMARY KEY     NOT NULL,\n"
                "STAT   INT                    NOT NULL\n"
                ");";

    ret = sqlite3_exec (sqlHdl, sql, 0, 0, 0);

#ifdef _DEBUG
    PRINTF("%s", sql);
    sSqlChkRet (sqlHdl, ret, __FUNCTION__);
#endif

    return ((SQLITE_OK == ret) ? OK : ERROR);
}

/*****************************************************************************
 * DECRIPTION:
 *      初始化 用户密码重置验证问题表 USER_VERIFY_TBL;
 * INPUTS:
 *      sqlite3* sqlHdl 数据库操作对象
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
                "Q3     TEXT                    NOT NULL\n"
                ");";

    ret = sqlite3_exec (sqlHdl, sql, 0, 0, 0);

#ifdef _DEBUG
    PRINTF("%s", sql);
    sSqlChkRet (sqlHdl, ret, __FUNCTION__);
#endif

    return ((SQLITE_OK == ret) ? OK : ERROR);
}


/*****************************************************************************
 * DECRIPTION:
 *      检验SQL函数执行结果
 * INPUTS:
 *      sqlite3* sqlHdl --  SQL处理对象
 *      STATUS ret --  相应的SQL函数返回值
 *      char* curOpera --   当前执行的操作名字
*****************************************************************************/
STATUS sSqlChkRet(sqlite3* sqlHdl, STATUS ret, const char* curOpera)
{
    STATUS stat = ERROR;

    //入参检查
    if (ISNULL(sqlHdl))
    {
        PRINTF("__%s__sqlHdl is NULL.", __FUNCTION__);
        return ret;
    }

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
 *      回调函数，打印表信息
 * INPUTS:
 *      void *execParam --    由 sqlite3_exec 的第四个参数提供
 *      int  colNum      --    每一行的列数
 *      char **colVal   --    表示行中字段值的字符串数组
 *      char **colName -- 表示列名称的字符串数组
*******************************************************************************/
int sDbShowTbl(void *execParam, int colNum, char **colVal, char **colName)
{
    int i;
    PRINTF("%s\n", (char*)execParam);
    for(i=0; i<colNum; i++){
        printf("%s = %s\n", colName[i], colVal[i] ? colVal[i] : "NULL");
    }
    printf("\n");
    return 0;
}

/*****************************************************************************
 * DECRIPTION:
 *      数据库的关闭操作
 * INPUTS:
 *      数据库操作对象 sqlite3* sqlHdl
*****************************************************************************/
void sDbClose(sqlite3 *sqlHdl)
{
    if (ISNULL(sqlHdl))
    {
        PRINTF("__%s__sqlHdl is NULL.", __FUNCTION__);
        EXIT(EXIT_FAILURE);
    }

    STATUS ret = sqlite3_close_v2(sqlHdl);
    if (SQLITE_OK == ret)
    {
        PRINTF("[DB Closed OK.]");
        return ;
    }
    else
    {
        PRINTF("[DB Closed Failed]");
        PRINTF ("\n");

#ifdef _DEBUG
    sSqlChkRet (sqlHdl, ret, __FUNCTION__);
#endif
        EXIT(EXIT_FAILURE);
    }
}

/*****************************************************************************
 * DECRIPTION:
 *      sDbInit()   初始化数据库：初始化所有表
 * INPUTS:
 *      sqlite3* sqlHdl;    数据库操作对象
*****************************************************************************/
STATUS sDbInit(sqlite3* sqlHdl)
{
    STATUS ret = ERROR;

    /*入参检查*/
    if( ISNULL(sqlHdl) )
    {
        PRINTF("__%s__sDbInit sqlHdl is NULL.", __FUNCTION__);
        goto o_exit;
    }

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
    else
    {
        PRINTF("%s: DB INIT OK.",__FUNCTION__);
    }

o_exit:
    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      sDbInsertData2PasswdTbl() 向数据库的USER_PASSWD_TBL表中添加数据(注册新用户)
 * INPUTS:
 *      sqlHdl    数据库操作对象
 *      uId       由系统生成的uid,
 *      uName     用户名
 *      uPasswd   用户密码
*****************************************************************************/
STATUS sDbInsertData2PasswdTbl(sqlite3* sqlHdl, T_UID uId, T_UNAME uName, T_UPASSWD uPasswd)
{
    STATUS ret = ERROR;

    /* 入参检查 */
    if (ISNULL(sqlHdl))
    {
#ifdef _DEBUG
        PRINTFILE;
#endif
        PRINTF("[%s: sqlHdl is NULL.]", __FUNCTION__);
        return ret;
    }

    //构造SQL语句
    char sql[SQL_LEN] = "INSERT INTO USER_PASSWD_TBL VALUES (";  //SQL语句
    char tmp[50] = {'\0'};   //临时拥有提取请求命令crReg中相关信息

    sprintf(tmp, "  %d,", uId);
    strncat(sql, tmp, strlen(tmp)); //填充sql语句的uid部分

    sprintf(tmp, "  '%s',", uName);
    strncat(sql, tmp, strlen(tmp)); //填充sql语句的用户名部分

    sprintf(tmp, "  '%s');", uPasswd);
    strncat(sql, tmp, strlen(tmp)); //填充sql语句的upasswd部分

    //执行SQL语句
#ifdef _DEBUG
    PRINTF("%s", sql);
#endif
    ret = sqlite3_exec (sqlHdl, sql,  NULL, NULL, NULL);
    sSqlChkRet (sqlHdl, ret, __FUNCTION__);

    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      sDbSelectConditionFromTbl 从表中select出符合条件的表项
 * INPUTS:
 *      sqlite3* sqlHdl 操作数据库对象
 *      char* condition 选择条件
 *      char* tblName   表名
*****************************************************************************/
STATUS sDbSelectConditionFromTbl(sqlite3 *sqlHdl, char *condition, char* tblName)
{
    STATUS ret = ERROR;
    char sql[SQL_LEN] = "SELECT ";
    char tmp[50] = {"\0"};

    /* 入参检查 */
    if (ISNULL(sqlHdl))
    {
#ifdef _DEBUG
        PRINTFILE;
#endif
        PRINTF("[%s: sqlHdl is NULL.]", __FUNCTION__);
        return ret;
    }

    PRINTF("condition:%s", condition);
    PRINTF("tblName:%s", tblName);

    /* 构造SQL语句 */
    sprintf(tmp, "%s", condition);
    strncat(sql, tmp, strlen(tmp));

    sprintf(tmp, "%s", " FROM ");
    strncat(sql, tmp, strlen(tmp));

    sprintf(tmp, "%s", tblName);
    strncat(sql, tmp, strlen(tmp));

    /* 执行SQL语句 */
#ifdef _DEBUG
    PRINTF("__%s__SQL:%s", __FUNCTION__, sql);
    ret = sqlite3_exec(sqlHdl, sql, sDbShowTbl, (void*)__FUNCTION__, NULL);
#else
    ret = sqlite3_exec(sqlHdl, sql, NULL, NULL, NULL);
#endif

    ret = sSqlChkRet (sqlHdl, ret, (const char*)__FUNCTION__);

    return ret;
}
