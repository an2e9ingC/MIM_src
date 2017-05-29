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
extern sqlite3** pSqlHdl;

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
 *      q1,q2     验证问题（2个）
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
        T_UVERIFIES q2
);


/*****************************************************************************
 * DECRIPTION:
 *      sDbDelDataFromPasswdTbl() 从数据库的USER_PASSWD_TBL表中删除一条数据
 * INPUTS:
 *      sqlite3* sqlHdl
 *      uid     由系统生成的uid,
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbDelDataFromPasswdTbl(sqlite3 *sqlHdl, T_UID uid);

/*****************************************************************************
 * DECRIPTION:
 *      sDbDelDataFromInfoTbl() 从数据库的 USER_INFO_TBL 表中删除一条数据
 * INPUTS:
 *      sqlite3* sqlHdl
 *      uid
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbDelDataFromInfoTbl(sqlite3 *sqlHdl, T_UID uid);

/*****************************************************************************
 * DECRIPTION:
 *      sDbDelDataFromFrdsTbl() 从数据库的 USER_FRDS_TBL 表中删除uid对应的所有数据
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
STATUS sDbDelDataFromFrdsTbl(sqlite3 *sqlHdl, T_UID uid);

/*****************************************************************************
 * DECRIPTION:
 *      sDbDelDataFromStatTbl() 从数据库的 USER_STAT_TBL 表中删除一条数据
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
STATUS sDbDelDataFromStatTbl(sqlite3 *sqlHdl, T_UID uid);

/*****************************************************************************
 * DECRIPTION:
 *      sDbDelDataFromVerifyTbl() 向数据库的 USER_VERIFY_TBL 表中删除一条数据
 * INPUTS:
 *      sqlite3* sqlHdl
 *      uid
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbDelDataFromVerifyTbl(sqlite3 *sqlHdl, T_UID uid);

/*****************************************************************************
 * DECRIPTION:
 *      sDbUpdateName 更新 USER_PASSWD_TBL 表中的 UNAME
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      newName 新的UNAME
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbUpdateName(sqlite3* sqlHdl, T_UID uid, T_UNAME newName);

/*****************************************************************************
 * DECRIPTION:
 *      sDbUpdateUPasswd 更新 USER_PASSWD_TBL 表中的 UPASSWD
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      newPasswd 新的密码
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbUpdatePasswd(sqlite3* sqlHdl, T_UID uid, T_UPASSWD newPasswd);

/*****************************************************************************
 * DECRIPTION:
 *      sDbUpdateUPasswd 更新 USER_INFO_TBL 表中的 SEX
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      newSex 性别
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbUpdateSex(sqlite3* sqlHdl, T_UID uid, T_USEX newSex);

/*****************************************************************************
 * DECRIPTION:
 *      sDbUpdateMail 更新 USER_INFO_TBL 表中的 EMAIL
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      newMail 新邮箱
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbUpdateMail(sqlite3* sqlHdl, T_UID uid, T_USEX newMail);

/*****************************************************************************
 * DECRIPTION:
 *      sDbUpdateTel 更新 USER_INFO_TBL 表中的 TEL
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      newTel 新电话
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbUpdateTel(sqlite3* sqlHdl, T_UID uid, T_UTEL newTel);

/*****************************************************************************
 * DECRIPTION:
 *      sDbUpdateRmk 更新 USER_FRDS_TBL 表中的 REMARK
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      newRmk 新备注
*****************************************************************************/
STATUS sDbUpdateRmk(sqlite3* sqlHdl, T_UID uid, T_FRD_REMARK newRmk);

/*****************************************************************************
 * DECRIPTION:
 *      sDbUpdateStat 更新 USER_STAT_TBL 表中的 STAT
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      newStat 新状态
***************************************************************/
STATUS sDbUpdateStat(sqlite3* sqlHdl, T_UID uid, T_USTAT newStat);

/*****************************************************************************
 * DECRIPTION:
 *      获取用户名,根据user的uid查找数据库将其对应的用户名填入user
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      name    保存获取的用户名
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      成功  -   用户名
 *      失败  -   NULL
 * CAUTIONS:
 *      调用要保证name参数能够足够大 来保存用户名
*****************************************************************************/
T_UNAME sDbGetName(sqlite3* sqlHdl, T_UID uid, T_UNAME name);

/*****************************************************************************
 * DECRIPTION:
 *      用户的数据库密文密码
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      passwd  保存获取的密码
*****************************************************************************/
T_UPASSWD sDbGetPasswd(sqlite3* sqlHdl, T_UID uid, T_UPASSWD passwd);

/*****************************************************************************
 * DECRIPTION:
 *      获取用户性别 USER_INFO_TBL并将其填入S_USER结构体
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      sex     保存获取的性别
*****************************************************************************/
T_USEX sDbGetSex(sqlite3* sqlHdl, T_UID uid, T_USEX sex);

/*****************************************************************************
 * DECRIPTION:
 *      获取用户email USER_INFO_TBL
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      mail    保存获取的邮箱
**************************************************************/
T_UMAIL sDbGetMail(sqlite3* sqlHdl, T_UID uid, T_UMAIL mail);


/*****************************************************************************
 * DECRIPTION:
 *      获取用户TEL USER_INFO_TBL
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      tel     保存获取的电话
*****************************************************************************/
T_UTEL sDbGetTel(sqlite3* sqlHdl, T_UID uid, T_UTEL tel);


/*****************************************************************************
 * DECRIPTION:
 *      获取用户好友列表 USER_FRDS_TBL
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      frdList 保存获取的好友列表
 * OUTPUTS:
 *      frdList 获取的好友列表
 * RETURN:
 *      好友的数量
*****************************************************************************/
 int sDbGetFrdsList(sqlite3* sqlHdl, T_UID uid, T_UID* frdList);

/*****************************************************************************
 * DECRIPTION:
 *      获取用户在线状态 USER_STAT_TBL
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
*****************************************************************************/
T_USTAT  sDbGetStat(sqlite3* sqlHdl, T_UID uid);

/*****************************************************************************
 * DECRIPTION:
 *      获取用户验证问题答案 USER_VERIFY_TBL
 * INPUTS:
 *      sqlHdl 操作数据库对象
 *      uid
 *      verifyArray 保存获取的验证问题数组
 * RETURN:
 *      T_UVERIFIES* 保存验证问题的数组
*****************************************************************************/
T_UVERIFIES *sDbGetVerify(sqlite3* sqlHdl, T_UID uid, T_UVERIFIES *verifyArray);

/*****************************************************************************
 * DECRIPTION:
 *      生成一个未用的用户id
 * INPUTS:
 *      sqlHdl
 * OUTPUTS:
 *      生成的uid
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
T_UID sDbGenUid(sqlite3* sqlHdl);

#endif // MIM_SERVER_H

