/*****************************************************************************
 * FILE NAME：
 *      mim_server_client_request.h
 * DESCRIPTION:
 *      用户服务器处理用户端的请求
 * AUTHOR:
 *      Michael Xu (xuchuaner@qq.com)
 * CREATED DATE:
 *      2017-05-26 14:33:52
 * MODIFICATION HISTORY:
 * --------------------------------------
 *
*****************************************************************************/

#ifndef MIM_SERVER_CLIENT_REQUEST_H
#define MIM_SERVER_CLIENT_REQUEST_H

#include "mim_sc_common.h"
#include "sqlite3.h"

/*****************************************************************************
 * DECRIPTION:
 *      处理用户的登录请求
 * INPUTS:
 *      T_UID uid,      用户id
 *      T_UPASSWD uPasswd    用户密码
 *      sqlite3 *sqlHdl  数据库
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      TRUE    认证合法
 *      FALSE   密码错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
BOOL sClientReqLogin(T_UID uid, T_UPASSWD uPasswd, sqlite3 *sqlHdl);

/*****************************************************************************
 * DECRIPTION:
 *      处理用户的注册请求
 * INPUTS:
 *      uName       用户名
 *      uPasswd    用户密码
 *      q1,q2    验证问题2个
 *      sqlite3** pSqlHdl  数据库
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      UID      --  注册成功,返回用户id
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
T_UID sClientReqRegister
(T_UNAME uName,
        T_UPASSWD uPasswd,
        T_UVERIFIES q1,
        T_UVERIFIES q2,
        sqlite3 **pSqlHdl
);


/*****************************************************************************
 * DECRIPTION:
 *      获取用户基本信息
 * INPUTS:
 *      S_USER** user   二级指针
 * OUTPUTS:
 *      S_USER** user
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbGetUserInfo(S_USER **user);

#endif // MIM_SERVER_CLIENT_REQUEST_H
