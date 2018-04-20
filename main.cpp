#include "MainWindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QtGlobal>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //setCodecForCStrings()
#if QT_VERSION < 0x050000
     QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
    MainWindow w;
    w.show();
    return a.exec();
}
