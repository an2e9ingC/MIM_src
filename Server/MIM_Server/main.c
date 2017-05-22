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

/*****************************************************************************
 * DECRIPTION:
 *      回调函数，当系统调用 sqlite3_exec 时的回调函数
 * INPUTS:
 *      void *NotUsed --    由 sqlite3_exec 的第四个参数提供
 *      int argc      --    每一行的列数
 *      char **argv   --    表示行中字段值的字符串数组
 *      char **azColName -- 表示列名称的字符串数组
 * OUTPUTS:
 *      NONE
 * RETURNS:
 *      OK      --  成功
 *      ERROR   --  失败
 *      INVALID_PARAM --  参数错误
 * CAUTIONS:
 *      NONE
*******************************************************************************/
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   printf("%s\n", (char*)NotUsed);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main()
{
    sqlite3 *sqlHdl = NULL; //SQL处理对象指针
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
    }

    /* 关闭数据库 */
    sDbClose (sqlHdl);
    PRINTF ("\n");

    return 0;
}
