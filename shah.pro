#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T15:19:57
#
#-------------------------------------------------

QT       += core gui network xml testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shah
TEMPLATE = app


SOURCES += main.cpp\
    MyConnectionWindow.cpp \
    MyBoardLogic.cpp \
    MyMenue.cpp \
    MyVec.cpp \
    PawTrans.cpp \
    MyUser.cpp \
    MainWindow.cpp \
    NetManager.cpp \
    Board.cpp

HEADERS  += \
    MyUser.h \
    MyConnectionWindow.h \
    MyBoardLogic.h \
    MyMenue.h \
    MyVec.h \
    PawTrans.h \
    Board.h \
    MainWindow.h \
    NetManager.h

DISTFILES +=

RESOURCES += \
    res.qrc
