/*****************************************************************************
 * FILE NAME：
 *      mim_server_client_request.c
 * DESCRIPTION:
 *      实现.h文件中的相关请求的处理函数
 * AUTHOR:
 *      Michael Xu (xuchuaner@qq.com)
 * CREATED DATE:
 *      2017-05-26 14:39:04
 * MODIFICATION HISTORY:
 * --------------------------------------
 *
*****************************************************************************/

#include "mim_server_client_request.h"
#include "mim_server_db.h"
#include <string.h>
#include <stdlib.h>



/*****************************************************************************
 * DECRIPTION:
 *      处理用户的登录请求
 * INPUTS:
 *      T_UID uid,      用户id
 *      T_UPASSWD uPasswd    用户密码
 *      sqlite3 *sqlHdl  数据库
*****************************************************************************/
BOOL sClientReqLogin(T_UID uid, T_UPASSWD uPasswd, sqlite3* sqlHdl)
{
    /*对比数据库查询的uid对应的passwd 判断密码是否相同*/
    T_UPASSWD dbPasswd = (T_UPASSWD)malloc(UPASSWD_LEN);
    bzero(dbPasswd, UPASSWD_LEN);
    sDbGetPasswd (sqlHdl, uid, dbPasswd);

    if (0 == strcmp(dbPasswd, uPasswd))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    free(dbPasswd);
}

/*****************************************************************************
 * DECRIPTION:
 *      处理用户的注册请求
 * INPUTS:
 *      uName       用户名
 *      uPasswd    用户密码
 *      q1,q2    验证问题2个
 *      sqlite3** sqlHdl  数据库
*****************************************************************************/
T_UID sClientReqRegister
(
        T_UNAME uName,
        T_UPASSWD uPasswd,
        T_UVERIFIES q1,
        T_UVERIFIES q2,
        sqlite3** pSqlHdl
)
{
    STATUS ret = ERROR;
    T_UID newUid = ERROR;
    PRINTF("NAME= %s, passwd = %s, q1=%s, q2=%s, sqlHdl=%s.",
           uName, uPasswd, q1, q2, (char*)*pSqlHdl);

    //在数据库中按照申请的先后顺序，依次分配id
    newUid = sDbGenUid(*pSqlHdl);
    if (0 >= newUid)
    {
#ifdef _DEBUG
        PRINTF("__%s__: 账号生成错误.", __FUNCTION__);
#endif
        return ERROR;
    }

    PRINTF("newUid = %d", newUid);
//    //向 USER_PASSWD_TBL 中添加新的用户名，密码
//    ret = sDbInsertData2PasswdTbl (sqlHdl, newUid, uName, uPasswd);
//    if (OK != ret)
//    {
//        return ERROR;
//#ifdef _DEBUG
//        PRINTF("__%s__: 用户名/密码添加错误.", __FUNCTION__);
//#endif
//    }

//    ret = sDbInsertData2VerifyTbl (sqlHdl, newUid, q1, q2);
//    if (OK != ret)
//    {
//        return ERROR;
//#ifdef _DEBUG
//        PRINTF("__%s__: 验证信息添加错误.", __FUNCTION__);
//#endif
//    }

//#ifdef _DEBUG
//    PRINTF("__%s__: 新用户(%d)注册成功", __FUNCTION__, newUid);
//#endif
    return OK;
}


/*****************************************************************************
 * DECRIPTION:
 *      获取用户基本信息（填充S_USER结构体的所有成员）
 * INPUTS:
 *      S_USER* user
 * OUTPUTS:
 *      S_USER* user
 * RETURNS:
 *      OK  处理成功
 *      ERROR   处理失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      确保入参不为NULL
*****************************************************************************/
STATUS sDbGetUserInfo(S_USER** user)
{
    STATUS ret = ERROR;

//    T_UNAME retName = (T_UNAME)malloc(UNAME_LEN);
//    bzero(retName, UNAME_LEN);
//    T_UPASSWD retPasswd = (T_UPASSWD)malloc(UPASSWD_LEN);
//    bzero(retPasswd, UPASSWD_LEN);
//    T_USEX retSex = (T_USEX)malloc(USEX_LEN);
//    bzero(retSex, USEX_LEN);
//    T_UMAIL retMail = (T_UMAIL)malloc(UMAIL_LEN);
//    bzero(retMail, UMAIL_LEN);
//    T_UMAIL retTel = (T_UMAIL)malloc(UTEL_LEN);
//    bzero(retTel, UTEL_LEN);
//    T_USTAT retStat = OFF_LINE;

    /* 入参检查 */
    if (ISNULL(user))
    {
#ifdef _DEBUG
        PRINTFILE;
        PRINTF("[%s: user is NULL.]", __FUNCTION__);
#endif
        return INVALID_PARAM;
    }

    /*调用db函数获取相关基本信息*/
//    sDbGetName(sqlHdl, user->id, retName);
//    sDbGetPasswd(sqlHdl, user->id, retPasswd);
//    sDbGetSex (sqlHdl, user->id, retSex);
//    sDbGetMail (sqlHdl, user->id, retMail);
//    sDbGetTel (sqlHdl, user->id, retTel);
//    retStat = sDbGetStat (sqlHdl, user->id);
    sDbGetName(sqlHdl, (*user)->id, (*user)->name);
    sDbGetPasswd(sqlHdl, (*user)->id, (*user)->passwd);
    sDbGetSex (sqlHdl,(*user)->id, (*user)->sex);
    sDbGetMail (sqlHdl, (*user)->id, (*user)->mail);
    sDbGetTel (sqlHdl, (*user)->id, (*user)->tel);
    (*user)->stat = sDbGetStat (sqlHdl, (*user)->id);

//    PRINTF("retUser uid = %d.\n"
//           "retUser name = %s.\n"
//           "retUser passwd = %s.\n"
//           "retUser sex = %s.\n"
//           "retUser mail = %s.\n"
//           "retUser TEL = %s.\n"
//           "retUser stat = %d.\n"
//           , user->id,
//           retName,
//           retPasswd,
//           retSex,
//           retMail,
//           retTel,
//           retStat);

    return ret;
}
