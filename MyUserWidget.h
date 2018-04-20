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
    void paintEvent(QPaintEvent*);
public:
    void setIsWhite(bool b);
    void setIsHuman(bool b);
    void setMyStep(bool b);
    void setIsUser(bool b);
    MyUser(QWidget *parent);

signals:

public slots:
};

#endif // MYUSER_H
