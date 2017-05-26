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
 *      获取用户基本信息
 * INPUTS:
 *      S_USER* user
 * OUTPUTS:
 *      S_USER* user
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*****************************************************************************/
STATUS sDbGetUserInfo(S_USER* user);

#endif // MIM_SERVER_CLIENT_REQUEST_H
