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

extern sqlite3 *sqlHdl;

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
STATUS sSqlChkRet(sqlite3 *sqlHdl, STATUS ret, const char *curOpera);

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
void sDbClose(sqlite3* sqlHdl);


/*****************************************************************************
 * DECRIPTION:
 *      sDbInit()   初始化数据库：初始化所有表
 * INPUTS:
 *      sqlite3 *slqHdl
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbInit(sqlite3 *slqHdl);

/*****************************************************************************
 * DECRIPTION:
 *      sDbInsertData2PasswdTbl() 向数据库的USER_PASSWD_TBL表中添加数据
 * INPUTS:
 *      sqlite3* sqlHdl
 *      uid     由系统生成的uid,
 *      name    用户名
 *      passwd  用户密码
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbInsertData2PasswdTbl
(
        sqlite3 *sqlHdl,
        T_UID uid,
        T_UNAME name,
        T_UPASSWD passwd
);

/*****************************************************************************
 * DECRIPTION:
 *      sDbInsertData2InfoTbl() 向数据库的 USER_INFO_TBL 表中添加数据
 * INPUTS:
 *      sqlite3* sqlHdl
 *      uid
 *      sex      性别
 *      mail,    邮箱
 *      tel      电话
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbInsertData2InfoTbl
(
    sqlite3 *sqlHdl,
    T_UID uid,
    T_USEX sex,
    T_UMAIL mail,
    T_UTEL tel
);

/*****************************************************************************
 * DECRIPTION:
 *      sDbInsertData2FrdsTbl() 向数据库的 USER_FRDS_TBL 表中添加数据
 * INPUTS:
 *      sqlite3* sqlHdl
 *      uid
 *      fid      好友id
 *      fRmk    好友备注
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbInsertData2FrdsTbl
(
    sqlite3 *sqlHdl,
    T_UID uid,
    T_UID fid,
    T_FRD_REMARK fRmk
);

/*****************************************************************************
 * DECRIPTION:
 *      sDbInsertData2StatTbl() 向数据库的 USER_STAT_TBL 表中添加数据
 * INPUTS:
 *      sqlite3* sqlHdl
 *      uId
 *      uStat     用户在线状态
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbInsertData2StatTbl(sqlite3 *sqlHdl, T_UID uid, T_USTAT uStat);

/*****************************************************************************
 * DECRIPTION:
 *      sDbInsertData2VerifyTbl() 向数据库的 USER_VERIFY_TBL 表中添加数据
 * INPUTS:
 *      sqlite3* sqlHdl
 *      uid
 *      q1,q2,q3     验证问题（3个）
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbInsertData2VerifyTbl
(
        sqlite3 *sqlHdl,
        T_UID uid,
        T_UVERIFIES q1,
        T_UVERIFIES q2,
        T_UVERIFIES q3
);

/*****************************************************************************
 * DECRIPTION:
 *      sDbSelectConditionFromTbl 从表中select出符合条件的表项，存到指针void* reslt中
 * INPUTS:
 *      sqlite3* sqlHdl 操作数据库对象
 *      char* condition 选择条件(需要是完整的SQL语句)
 *      void* reslt     存放查询的结果
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      由于结果的数据结构不定，因此使用void*，最后要根据实际情况进行转化
*****************************************************************************/
STATUS sDbSelectConditionFromTbl(sqlite3* sqlHdl, char* condition, void* reslt);


#endif // MIM_SERVER_H
