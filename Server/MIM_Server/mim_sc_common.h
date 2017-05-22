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
    cFrdRemarkModify,    //好友备注信息修改

    /* Server 回复命令标志 */
    sLogin,   //登录-请求回复
    sRegister,    //注册-请求回复
    sResetPasswd, //重置密码-请求回复
    sInfoSync, //用户信息同步-请求回复
    sUDPConnct,   //建立用户UDP连接-请求回复
    sFrdAdd,   //添加好友-请求回复
    sFrdDel,   //删除好友-请求回复
    sFrdRemarkModify,    //好友备注信息修改-请求回复

}T_CSCMD;

/* 自定义输出方式，使用fflush刷新，防止缓冲导致的输出不完整 */
#define PRINTF(format, args...) \
    printf("\n"format, ##args); \
    fflush(stdout)

/* 在DEBUG模式下，用于打印出错文件 */
#define PRINTFILE \
    printf("\n__%s__ Line:_%d_\n", __FILE__, __LINE__)

#define EXIT(Exit) \
    printf("\n");\
    exit(Exit)

/* 检查指针是否为空NULL */
#define ISNULL(Q) \
    ((NULL == (void*)Q) ? TRUE : FALSE)

/* 数据库相关数据类型定义 */
typedef unsigned int T_UID; // 用户id数据类型
typedef char* T_UNAME;  // 用户名数据类型(限定长度32字符)
typedef char* T_UPASSWD;    // 密码数据类型(限定长度6-14) 因为字符串的结束符要要占一位
typedef char* T_UVERIFIES;  // 验证信息
typedef char* T_FRD_REMARK;  //好友备注名数据类型
typedef char* T_USEX;   //用户性别
typedef char* T_UMAIL;  //用户邮箱
typedef char* T_UTEL;   //用户电话
typedef char* T_Q;  //用户验证信息
typedef enum {
    ON_LINE = 1,
    OFF_LINE
}T_USTAT;   //用户在线状态


/* 根据通信协议设计的通信命令结构体 */
//Client登录请求
typedef struct {
    T_CSCMD cmd;    //请求命令
    T_UID uId;  //用户id
    T_UPASSWD uPasswd;  //用户密码
}CR_LOGIN;

//Client注册请求
typedef struct {
    T_CSCMD cmd;    //请求命令
    T_UNAME uName;
    T_UVERIFIES Q1; //验证信息*2
    T_UVERIFIES Q2;
    T_UPASSWD uPasswd;
}CR_REG;

//Client密码重置请求
typedef struct {
    T_CSCMD cmd;
    T_UID uId;
    T_UVERIFIES Q1;
    T_UVERIFIES Q2;
}CR_RESET;

//Client信息同步请求
typedef struct {
    T_CSCMD cmd;
    T_UID uId;
}CR_SYNC;

typedef struct {
    T_CSCMD cmd;
    T_UID uId;
    T_UID fId;  //要删除的好友ID
}CR_DEL_FRD;  //Client删除好友请求

//Client添加好友请求
typedef struct {
    T_CSCMD cmd;
    T_UID uId;
    T_UID fId;  //要添加的好友ID
}CR_ADD_FRD;

//Client修改好友备注请求
typedef struct {
    T_CSCMD cmd;
    T_UID uId;
    T_UID fId;  //要修改的好友ID
    T_FRD_REMARK newRmk;    //新的好友备注
}CR_MDF_RMK;

//Server由于处理结果简单且格式相同，使用统一的回复结构(除了同步信息)
typedef struct {
    T_CSCMD cmd;
    T_UID uId;
    BOOL result;    //服务器的处理结果：TURE/FALSE
}SR_GEN;

#define FRD_COUNT_LIMIT 100   //好友数量上限

//服务器回复好友信息同步
typedef struct{
    T_CSCMD cmd;
    T_UID uId;
    int frdCount;   //好友数量
    T_UID frdList[FRD_COUNT_LIMIT]; //好友id信息数组(最多100人)
}SR_SYNC;


#endif // MIM_SC_COMMON_H
