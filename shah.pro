#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T15:19:57
#
#-------------------------------------------------

QT       += core gui network xml testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shah
TEMPLATE = app

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
    MyBoardLogic.cpp \
    MyVec.cpp \
    MainWindow.cpp \
    NetManager.cpp \
    PawTransView.cpp \
    BoardWidget.cpp \
    MyUserWidget.cpp \
    MyMenueWidget.cpp \
    MyConnectionStatusWidget.cpp

HEADERS  += \
    MyBoardLogic.h \
    MyVec.h \
    MainWindow.h \
    NetManager.h \
    PawTransView.h \
    BoardWidget.h \
    MyUserWidget.h \
    MyMenueWidget.h \
    MyConnectionStatusWidget.h \
    Models.h

DISTFILES +=

RESOURCES += \
    res.qrc
