#include "mainwindow.h"
#include <QApplication>
#ifdef QT_DEBUG
    //#include <QTest>
    //#include <iostream>
    //#include <test_MyBoardLogic.h>
    using namespace std;
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
#ifdef QT_DEBUG
   //freopen("testing.log", "w", stdout);
   //QTest::qExec(new test_MyBoardLogic, argc, argv);
#endif

    return a.exec();
}
