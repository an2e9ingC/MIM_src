TEMPLATE = app
CONFIG += console network
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    mim_server_db.c \
    main.c

HEADERS += \
    mim_sc_common.h \
    sqlite3.h \
    mim_server_db.h

LIBS += -lsqlite3

DISTFILES +=
