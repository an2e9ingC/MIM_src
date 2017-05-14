/*****************************************************************************
 * FILE NAME：
 *      mim_sc_common.h
 * DESCRIPTION:
 *      声明客户端和服务器端通用的宏及常量
 * AUTHOR:
 *      Michael Xu (xuchuaner@qq.com)
 * CREATED DATE:
 *      2017.05.09-15:40
 * MODIFICATION HISTORY:
 * --------------------------------------
 *  2017-05-14 23:25:36 添加了自定义的PRINTF,EXIT宏
*****************************************************************************/

#ifndef MIM_SC_COMMON_H
#define MIM_SC_COMMON_H

#include <stdio.h>

/* 调试开关 */
#define _DEBUG
/* 严格调试模式开关,在此模式下，任何警告错误都会结束程序进程 */
#define _STRICT_DEBUG

/* 定义函数返回值 */
typedef int STATUS;  //定义函数/服务器返回的处理结果数据类型，用int表示
#define OK (0)       //处理成功
#define ERROR (-1)    //处理失败
#define INVALID_PARAM  (-2)   //输入的参数无效

/* 定义服务器处理客户端请求后的结果 */
typedef int BOOL;   //处理结果使用自定义的BOOL类型
#define TRUE    (0)
#define FALSE   (-1)

/* 用户id数据类型 */
typedef unsigned int T_UID;

/* 用户名数据类型(限定长度32字符) */
typedef char* T_UNAME;

/* 密码数据类型(限定长度6-14) 因为字符串的结束符要要占一位*/
typedef char* T_UPASSWD;

/* 好友备注名数据类型 */
typedef char* T_FRD_MEMO_NAME;

/* 定义C/S之间的通信命令标志，使用枚举类csCmd来表示，用于C/S之间命令鉴别 */
typedef enum e_CommonCmd{
    /*Client 请求命令标志 */
    cLogin = 1,   //登录
    cRegister,    //注册
    cResetPasswd, //重置密码
    cInfoSync, //用户信息同步
    cUDPConnct,   //建立用户UDP连接
    cFrdAdd,   //添加好友
    cFrdDel,   //删除好友
    cFrdMemoModify,    //好友备注信息修改

    /* Server 回复命令标志 */
    sLogin,   //登录-请求回复
    sRegister,    //注册-请求回复
    sResetPasswd, //重置密码-请求回复
    sInfoSync, //用户信息同步-请求回复
    sUDPConnct,   //建立用户UDP连接-请求回复
    sFrdAdd,   //添加好友-请求回复
    sFrdDel,   //删除好友-请求回复
    sFrdMemoModify,    //好友备注信息修改-请求回复

}T_CSCMD;

/* 自定义输出方式，使用fflush刷新，防止缓冲导致的输出不完整 */
#define PRINTF(format, args...) \
    printf("\n"format, ##args); \
    fflush(stdout)

#define EXIT(Exit) \
    printf("\n");\
    exit(Exit)



#endif // MIM_SC_COMMON_H
