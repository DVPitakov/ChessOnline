#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T15:19:57
#
#-------------------------------------------------

QT       += core gui network multimedia xml websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shah
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    MyNet.cpp \
    mylabel.cpp \
    pawtrans.cpp \
    mymenue.cpp \
    variant.cpp \
    board.cpp \
    WebSocketsConnector.cpp \
    MuUser.cpp \
    MyConnectionWindow.cpp \
    MyPlayer.cpp \
    myvec.cpp

HEADERS  += mainwindow.h \
    MyNet.h \
    mylabel.h \
    pawtrans.h \
    mymenue.h \
    variant.h \
    board.h \
    WebSocketsConnector.h \
    MyUser.h \
    MyConnectionWindow.h \
    MyPlayer.h \
    myvec.h

DISTFILES +=

RESOURCES += \
    res.qrc
