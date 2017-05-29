TEMPLATE = app
CONFIG += console network
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    mim_server_db.c \
    main.c \
    mim_server_client_request.c \
    server_socket.c

HEADERS += \
    mim_sc_common.h \
    sqlite3.h \
    mim_server_db.h \
    mim_server_client_request.h \
    server_socket.h

LIBS += \
    -lsqlite3 \
    -lpthread

DISTFILES +=

QMAKE_CFLAGS += -Wno-unused-variable\
    -Wno-unused-parameter \
    -Wno-unused-function
