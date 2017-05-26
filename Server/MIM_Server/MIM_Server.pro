TEMPLATE = app
CONFIG += console network
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    mim_server_db.c \
    main.c \
    mim_server_client_request.c

HEADERS += \
    mim_sc_common.h \
    sqlite3.h \
    mim_server_db.h \
    mim_server_client_request.h

LIBS += -lsqlite3

DISTFILES +=
