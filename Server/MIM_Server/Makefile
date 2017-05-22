LIBS = -lsqlite3
HEADERS = mim_sc_common.h \
		  mim_server_db.h \
		  sqlite3.h \

#各个模块的输出文件
objects = main.o \
		  server_db.o


#最终生成的目标可执行文件
all: mim_server
.PHONY:all

mim_server: $(objects)
	gcc $(objects) $(LIBS) -o mim_server
	-rm -f $(objects)


#具体各个模块编译依
main.o :  mim_server_db.h mim_sc_common.h
	gcc -c main.c  -o  main.o 

server_db.o : 
	gcc -c mim_server_db.c -o server_db.o
	
#生成调试文件
dbg: debug

debug: $(objects)
	gcc -g $(objects) $(LIBS) -o debug
	-rm -f $(objects)

.PHONY:clean
clean:
	rm -f $(objects) *.~  *.out  mim_server  users.db debug
