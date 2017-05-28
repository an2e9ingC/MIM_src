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
    BOOL ret = FALSE;

    /*对比数据库查询的uid对应的passwd 判断密码是否相同*/

    return ret;

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
STATUS sDbGetUserInfo(S_USER* user)
{
    STATUS ret = ERROR;

    /* 入参检查 */
    if (ISNULL(user))
    {
#ifdef _DEBUG
        PRINTFILE;
        PRINTF("[%s: user is NULL.]", __FUNCTION__);
#endif
        return INVALID_PARAM;
    }

    /*调用static函数获取相关基本信息*/
//    ret = sDbGetName(user);
//    ret = sDbGetPasswd(user);
//    ret = sDbGetSex (user);
//    ret = sDbGetMail (user);
//    ret = sDbGetTel (user);
//    ret = sDbGetFrdsList(user);
//    ret = sDbGetStat (user);
//    ret = sDbGetVerify(user);

    return ret;
}
