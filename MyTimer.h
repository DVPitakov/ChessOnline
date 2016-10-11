#ifndef MYTIMER_H
#define MYTIMER_H

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QTime>
#include <QPaintEvent>

class MyTimer : public QWidget
{
    Q_OBJECT
    void paintEvent(QPaintEvent * event) {
        QPainter painter(this);
        painter.drawText(0,0,this->width(),this->height(), Qt::AlignCenter, QString::number(myTime));
    }
public:
    int myTime{60};
    QTimer * timer;
    explicit MyTimer(QWidget *parent = 0);


signals:
    timeOut();
public slots:
    void setTime(int time) {
        myTime = time;
        updateTime();
    }
    void updateTime() {
        update();
        if (myTime >= 1) {
            timer->start(1000);
            myTime -= 1;
        }
        else {
            emit timeOut();
        }


    }
};

#endif // MYTIMER_H
