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
 *      2017-05-15 11:21:49 重新设置sSqlChkRet函数为非static，对外提供接口
 *      2017-05-22 11:35:41 取消sDbOpen函数，sDbClose返回值为void
*****************************************************************************/

#ifndef MIM_SERVER_DB_H
#define MIM_SERVER_DB_H

#define DB_FILE "users.db"

#include <sqlite3.h>
#include "mim_sc_common.h"

#define SQL_LEN 200 //定义SQL语句长度

/*****************************************************************************
 * DECRIPTION:
 *      回调函数，打印表信息
 * INPUTS:
 *      void *execParam --    由 sqlite3_exec 的第四个参数提供
 *      int  colNum      --    每一行的列数
 *      char **colVal   --    表示行中字段值的字符串数组
 *      char **colName -- 表示列名称的字符串数组
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      返回执行结果
 * CAUTIONS:
 *      NONE
*******************************************************************************/
int sDbShowTbl(void *execParam, int colNum, char **colVal, char **colName);

/*****************************************************************************
 * DECRIPTION:
 *      检验SQL函数执行结果
 * INPUTS:
 *      sqlite3* sqlHdl --  SQL处理对象
 *      STATUS ret --  相应的SQL函数返回值
 *      char* curOpera --   当前执行的操作名字
 * OUTPUTS:
 *      OK (0)       结果正常
 *      ERROR (-1)   结果异常
 * RETURNS:
 *      NONE
 * CAUTIONS:
 *      本函数用于DEBUG模式输出
*****************************************************************************/
STATUS sSqlChkRet(sqlite3* sqlHdl, STATUS ret, const char *curOpera);

/***********************************************
 * DECRIPTION:
 *      数据库的关闭操作
 * INPUTS:
 *      数据库操作对象 sqlHdl
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      NONE
 * CAUTIONS:
 *      NONE
*****************************************************************************/
void sDbClose(sqlite3 *sqlHdl);


/*****************************************************************************
 * DECRIPTION:
 *      sDbInit()   初始化数据库：初始化所有表
 * INPUTS:
 *      sqlite3* sqlHdl; 数据库对象
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbInit(sqlite3* sqlHdl);

/*****************************************************************************
 * DECRIPTION:
 *      sDbInsertData2PasswdTbl() 向数据库的USER_PASSWD_TBL表中添加数据
 * INPUTS:
 *      sqlite3*    数据库操作对象
 *      T_UID uId   由系统生成的uid,
 *      T_UNAME     用户名
 *      T_UPASSWD   用户密码
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbInsertData2PasswdTbl(sqlite3*, T_UID, T_UNAME, T_UPASSWD);

/*****************************************************************************
 * DECRIPTION:
 *      sDbSelectConditionFromTbl 从表中select出符合条件的表项
 * INPUTS:
 *      sqlite3* sqlHdl 操作数据库对象
 *      char* condition 选择条件
 *      char* tblName   表名
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbSelectConditionFromTbl(sqlite3* sqlHdl, char* condition, char *tblName);

#endif // MIM_SERVER_H
