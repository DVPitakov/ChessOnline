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
    pawtrans.cpp \
    mymenue.cpp \
    board.cpp \
    WebSocketsConnector.cpp \
    MuUser.cpp \
    MyConnectionWindow.cpp \
    myvec.cpp \
    MyTimer.cpp \
    MyBoardLogic.cpp

HEADERS  += mainwindow.h \
    pawtrans.h \
    mymenue.h \
    WebSocketsConnector.h \
    MyUser.h \
    MyConnectionWindow.h \
    myvec.h \
    MyTimer.h \
    MyBoardLogic.h \
    board.h

DISTFILES +=

RESOURCES += \
    res.qrc
