TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    mim_server_db.c

HEADERS += \
    mim_sc_common.h \
    sqlite3.h \
    mim_server_db.h

LIBS += -lsqlite3
