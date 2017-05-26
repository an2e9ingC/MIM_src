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
 *      获取用户名
 * INPUTS:
 *      S_USER* user
 * OUTPUTS:
 *      S_USER* user
 * RETURNS:
 *      OK  处理成功
 *      ERROR   处理失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      static
*****************************************************************************/
static STATUS sDbGetName(S_USER *user)
{
    STATUS ret = ERROR;
    T_UNAME uName = (T_UNAME)malloc(UNAME_LEN);
    T_UID uId = user->id;
//    char* condition = "";

//    sqlite3_exec ()


    free(uName);
    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      用户的数据库密文密码
 * INPUTS:
 *      S_USER* user
*****************************************************************************/
static STATUS sDbGetPasswd(S_USER *user)
{
    STATUS ret = ERROR;


    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      获取用户性别 USER_INFO_TBL并将其填入S_USER结构体
 * INPUTS:
 *      S_USER* user
*****************************************************************************/
static STATUS sDbGetSex(S_USER* user)
{
    STATUS ret = ERROR;


    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      获取用户email USER_INFO_TBL
 * INPUTS:
 *      S_USER* user
**************************************************************/
static STATUS sDbGetMail(S_USER* user)
{
    STATUS ret = ERROR;


    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      获取用户TEL USER_INFO_TBL
 * INPUTS:
 *      S_USER* user
*****************************************************************************/
static STATUS sDbGetTel(S_USER* user)
{
    STATUS ret = ERROR;


    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      获取用户好友列表 USER_FRDS_TBL
 * INPUTS:
 *      S_USER* user
*****************************************************************************/
static STATUS sDbGetFrdsList(S_USER* user)
{
    STATUS ret = ERROR;


    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      获取用户在线状态 USER_STAT_TBL
 * INPUTS:
 *      S_USER* user
*****************************************************************************/
static STATUS sDbGetStat(S_USER* user)
{
    STATUS ret = ERROR;


    return ret;
}

/*****************************************************************************
 * DECRIPTION:
 *      获取用户验证问题答案 USER_VERIFY_TBL
 * INPUTS:
 *      S_USER* user
*****************************************************************************/
static STATUS sDbGetVerify(S_USER* user)
{
    STATUS ret = ERROR;


    return ret;
}

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
    ret = sDbGetName(user);
    ret = sDbGetPasswd(user);
    ret = sDbGetSex (user);
    ret = sDbGetMail (user);
    ret = sDbGetTel (user);
    ret = sDbGetFrdsList(user);
    ret = sDbGetStat (user);
    ret = sDbGetVerify(user);

    return ret;
}
