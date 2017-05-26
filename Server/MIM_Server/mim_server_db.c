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
 *      回调函数，打印表信息(主要是用户调试模式)
 * INPUTS:
 *      void *execParam --    由 sqlite3_exec 的第四个参数提供
 *      int  colNum      --    每一行的列数
 *      char **colVal   --    表示行中字段值的字符串数组
 *      char **colName -- 表示列名称的字符串数组
*******************************************************************************/
static int sDbShowTbl(void *execParam, int colNum, char **colVal, char **colName)
{
    int i;
    PRINTF("%s", (char*)execParam);
    for(i=0; i<colNum; i++){
        printf("%s = %s\n", colName[i], colVal[i] ? colVal[i] : "NULL");
        printf("%s\n", colVal[i] ? colVal[i] : "NULL");
    }
    PRINTF("\n");
    return 0;
}

/*****************************************************************************
 * DECRIPTION:
 *      回调函数，将查询的内容保存到入参 void* reslt
 * INPUTS:
 *      void *reslt     --  用于保存查询到的数据
 *      int  colNum     --  每一行的列数
 *      char **colVal   --  表示行中字段值的字符串数组
 *      char **colName  --  表示列名称的字符串数组
*******************************************************************************/
static int sDbSave2Reslt(void *reslt, int colNum, char **colVal, char **colName)
{
    int i;
    char * tmp = NULL;

    for(i=0; i<colNum; i++){
        tmp = colVal[i] ? colVal[i] : "NULL";
        memcpy (reslt, tmp, strlen(tmp));
    }
#ifdef   _DEBUG
    PRINTF("__%s__:", __FUNCTION__);
    PRINTF("sizeof(?:) = %lu.\n"
           "strlen() = %lu.\n"
           "reslt = %s.",
           sizeof(tmp),
           strlen(tmp),
           (char*)reslt);
#endif
    return 0;
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
STATUS sDbInit(sqlite3 *slqHdl)
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
 *      (使用全局通用的sqlHdl)
 *      uid     由系统生成的uid,
 *      name    用户名
 *      passwd  用户密码
*****************************************************************************/
STATUS sDbInsertData2PasswdTbl(sqlite3* sqlHdl, T_UID uid, T_UNAME name, T_UPASSWD passwd)
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

    sprintf(tmp, "  %d,", uid);
    strncat(sql, tmp, strlen(tmp)); //填充sql语句的 UID 部分

    sprintf(tmp, "  '%s',", name);
    strncat(sql, tmp, strlen(tmp)); //填充sql语句的 UNAME 部分

    sprintf(tmp, "  '%s');", passwd);
    strncat(sql, tmp, strlen(tmp)); //填充sql语句的 UPASSWD 部分

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
 *      sDbInsertData2InfoTbl() 向数据库的 USER_INFO_TBL 表中添加数据
 * INPUTS:
 *      sqlite3* sqlHdl
 *      uid
 *      sex      性别
 *      mail,    邮箱
 *      tel      电话
*****************************************************************************/
STATUS sDbInsertData2InfoTbl
(
        sqlite3 *sqlHdl,
        T_UID uid,
        T_USEX sex,
        T_UMAIL mail,
        T_UTEL tel)
{
    STATUS ret = ERROR;

    /* 入参检查 */
    if (ISNULL(sqlHdl))
    {
#ifdef _DEBUG
        PRINTFILE;
#endif
        PRINTF("[%s: sqlHdl is NULL.]", __FUNCTION__);
        return INVALID_PARAM;
    }

    //构造SQL语句
    char sql[SQL_LEN] = "INSERT INTO USER_INFO_TBL VALUES (";  //SQL语句
    char tmp[50] = {'\0'};

    sprintf(tmp, "  %d,", uid);
    strncat(sql, tmp, strlen(tmp)); //填充sql语句的 UID 部分

    sprintf(tmp, "  '%s',", sex);
    strncat(sql, tmp, strlen(tmp)); //填充sql语句的 SEX 部分

    sprintf(tmp, "  '%s',", mail);
    strncat(sql, tmp, strlen(tmp)); //填充sql语句的 EMAIL 部分

    sprintf(tmp, "  '%s');", tel);
    strncat(sql, tmp, strlen(tmp)); //填充sql语句的 TEL 部分

    //执行SQL语句
    ret = sqlite3_exec (sqlHdl, sql,  NULL, NULL, NULL);

#ifdef _DEBUG
    PRINTF("%s", sql);
    sSqlChkRet (sqlHdl, ret, __FUNCTION__);
#endif

    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      sDbInsertData2FrdsTbl() 向数据库的 USER_FRDS_TBL 表中添加数据
 * INPUTS:
 *      sqlite3* sqlHdl
 *      uid
 *      fid      好友id
 *      fRmk    好友备注
*****************************************************************************/
STATUS sDbInsertData2FrdsTbl(sqlite3 *sqlHdl, T_UID uid, T_UID fid, T_FRD_REMARK fRmk)
{

}

/*****************************************************************************
 * DECRIPTION:
 *      sDbInsertData2StatTbl() 向数据库的 USER_STAT_TBL 表中添加数据
 * INPUTS:
 *      sqlite3* sqlHdl
 *      T_UID uId
 *      T_USTAT     用户在线状态
*****************************************************************************/
STATUS sDbInsertData2StatTbl(sqlite3 *sqlHdl, T_UID uid, T_USTAT uStat)
{

}

/*****************************************************************************
 * DECRIPTION:
 *      sDbInsertData2VerifyTbl() 向数据库的 USER_VERIFY_TBL 表中添加数据
 * INPUTS:
 *      sqlite3* sqlHdl
 *      T_UID
 *      T_UVERIFIES     验证问题（3个）
 *      T_UVERIFIES
 *      T_UVERIFIES
*****************************************************************************/
STATUS sDbInsertData2VerifyTbl
(sqlite3 *sqlHdl,
        T_UID uid,
        T_UVERIFIES q1,
        T_UVERIFIES q2,
        T_UVERIFIES q3
)
{

}


/*****************************************************************************
 * DECRIPTION:
 *      sDbSelectConditionFromTbl 从表中select出符合条件的表项
 * INPUTS:
 *      sqlite3* sqlHdl 操作数据库对象
 *      char* condition 选择条件(需要是完整的SQL语句)
 *      void* reslt     存放查询的结果
*****************************************************************************/
STATUS sDbSelectConditionFromTbl(sqlite3 *sqlHdl, char *condition, void *reslt)
{
    STATUS ret = ERROR;

    /* 入参检查 */
    if (ISNULL(sqlHdl))
    {
#ifdef _DEBUG
        PRINTFILE;
        PRINTF("[%s: sqlHdl is NULL.]", __FUNCTION__);
#endif
        return INVALID_PARAM;
    }

    /* 执行SQL语句 */
    ret = sqlite3_exec(sqlHdl, condition, sDbSave2Reslt, reslt, NULL);

    ret = sSqlChkRet (sqlHdl, ret, (const char*)__FUNCTION__);

    return ret;
}
