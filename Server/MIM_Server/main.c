/*****************************************************************************
 * FILE NAME：
 *      main.c
 * DESCRIPTION:
 *      服务器端的函数入口和主程序
 * AUTHOR:
 *      Michael Xu (xuchuaner@qq.com)
 * CREATED DATE:
 *      2017.05.09
 * MODIFICATION HISTORY:
 * --------------------------------------
 *
*****************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sqlite3.h>

#include "mim_sc_common.h"
#include "mim_server_db.h"

sqlite3 *sqlHdl = NULL; //SQL处理对象指针

int main()
{
    STATUS ret = ERROR;

    PRINTF("-------------------------------------\n"
           "MIM SERVER INITIALIZING...\n"
           "-------------------------------------\n");

    /* 打开数据库 */
    ret = sqlite3_open (DB_FILE, &sqlHdl);
    if (SQLITE_OK == ret)
    {
        PRINTF("[DB open ok.]");
    }
    else
    {
        PRINTF("[DB open failed.]");
        EXIT(EXIT_FAILURE);
    }

    /* 初始化数据库即相关表 */
    ret = sDbInit(sqlHdl);
    if (OK == ret)
    {
        PRINTF("DB:%s Init OK.", DB_FILE);
        PRINTF("-------------------------------------\n"
               "MIM SERVER INITIALIZATION COMPLETED!\n"
               "-------------------------------------\n");
    }
    else
    {
        PRINTF("DB:%s Init ERROR.", DB_FILE);
        PRINTF("-------------------------------------\n"
               "MIM SERVER INITIALIZATION FAILED!\n"
               "-------------------------------------\n");
        EXIT(EXIT_FAILURE);
    }


    /************test**************/
    CR_REG *reg = (CR_REG *)malloc(sizeof(CR_REG));
    reg->uName = "xuchuan";
    reg->Q1 = "China";
    reg->Q2 = "1994";
    reg->uPasswd= "adsjfasiofajg";

    T_UID uid = 8;
    ret = sDbInsertData2PasswdTbl(sqlHdl, uid, reg->uName, reg->uPasswd);
    if(OK != sSqlChkRet (sqlHdl, ret, "test insert"))
    {
        PRINTF("__sDbInsertData2PasswdTbl__: FAILED.");
        return -1;
    }
    else
    {
        PRINTF("__sDbInsertData2PasswdTbl__: OK.");
    }

    free(reg);

    sDbInsertData2InfoTbl(sqlHdl, uid, "male", "xuchuaner@qq.com", "1810101");
    sDbInsertData2FrdsTbl(sqlHdl, uid, 111, "ftest1");
    sDbInsertData2StatTbl(sqlHdl, uid, ON_LINE);
    sDbInsertData2VerifyTbl(sqlHdl, uid, "yanzheng1", "yanzheng2", "yanzheng3");

    T_UPASSWD passwd = (T_UPASSWD)malloc (UPASSWD_LEN);

    ret = sDbSelectConditionFromTbl(sqlHdl,
                                    "SELECT UPASSWD FROM USER_PASSWD_TBL WHERE UID=8;",
                                    passwd);
    free(passwd);

    if(OK != sSqlChkRet (sqlHdl, ret, "test select"))
    {
        PRINTF("__sDbSelectConditionFromTbl__: FAILED.");
        return -1;
    }
    else
    {
        PRINTF("__sDbSelectConditionFromTbl__: OK.");
    }

    /************test**************/

    /* 关闭数据库 */
    sDbClose (sqlHdl);
    PRINTF ("\n");

    return 0;
}
