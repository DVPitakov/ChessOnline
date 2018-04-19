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
    void paintEvent(QPaintEvent* event) {
        QImage userImage2;
        if (isWhite) {
           userImage2 = whiteImg.scaled(this->width() * 0.9,this->height() * 0.8);
        }
        else {
           userImage2 = blackImg.scaled(this->width() * 0.9,this->height() * 0.8);
        }

        QPainter painter(this);

        painter.setBrush(Qt::white);
        painter.setPen(Qt::gray);
        if(myStep) {
            QPen pen = painter.pen();
            QPen newPen;
            newPen.setWidth(2);
            newPen.setColor(Qt::green);
            painter.drawRect(0,0,width() - 1, height() - 1);
            painter.setPen(pen);
        }
        else {
            painter.drawRect(0,0,width() - 1, height() - 1);
        }

        if(isUser) {
            painter.setPen(Qt::black);
            painter.drawText(0, height() * 0.9, width(), height() * 0.1, Qt::AlignCenter, "user");
        }


        QString str = (isWhite)?"white":"black";
        painter.drawText(0,0,  width(),  0.1 * height(), Qt::AlignCenter, str);


        painter.drawImage(0.05 * width(),height() * 0.1,userImage2);
        painter.drawText(width() , this->height(), QString("text"));


    }
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
