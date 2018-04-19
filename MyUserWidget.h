#ifndef MYUSER_H
#define MYUSER_H

#include <QObject>
#include <QWidget>
#include <QImage>
#include <QPaintEvent>
#include <QPainter>

class MyUser:public QWidget
{
    Q_OBJECT
private:
    QImage whiteImg;
    QImage blackImg;
    bool isUser{0};
    bool isHuman{0};
    bool myStep{0};
    bool isWhite{0};
    void paintEvent(QPaintEvent* event);
public:
    void setIsWhite(bool b) {isWhite = b; update();}
    void setIsHuman(bool b) {isHuman = b; update();}
    void setMyStep(bool b) {myStep = b; update();}
    void setIsUser(bool b) {isUser = b; update();}
    MyUser(QWidget *parent);

signals:

public slots:
};

#endif // MYUSER_H
