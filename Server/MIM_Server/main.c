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
    char *sql;
    char *zErrMsg;

    /* 打开数据库 */
    ret = sDbOpen (DB_FILE, sqlHdl);
    sSqlChkRet (sqlHdl, ret, "OpenDB");

    sql = "CREATE TABLE test("  \
          "ID INT PRIMARY KEY     NOT NULL," \
          "NAME           TEXT    NOT NULL," \
          "AGE            INT     NOT NULL," \
          "ADDRESS        CHAR(50)," \
          "SALARY         REAL );";
    /* Execute SQL statement */
    ret = sqlite3_exec(sqlHdl, sql, 0, 0, &zErrMsg);
    if( ret != SQLITE_OK ){
        fprintf(stdout, "Table created failed:%s\n", zErrMsg);
        EXIT(EXIT_FAILURE);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }


    /* 初始化数据库即相关表 */
//    ret = sDbInit(sqlHdl);
//    if (OK == ret)
//    {
//        printf("DB:%s Init OK.", DB_FILE);
//    }
//    else
//    {
//        printf("DB:%s Init ERROR.", DB_FILE);
//        EXIT(EXIT_FAILURE);
//    }

    /* 关闭数据库 */
    sDbClose (sqlHdl);

    return 0;
}
