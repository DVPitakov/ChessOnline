#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

class MyButton : public QWidget
{
    Q_OBJECT
    QString _text;
public:
    void mouseReleaseEvent(QMouseEvent*) {
        emit clicked(0);
    }

    void paintEvent(QPaintEvent *) {

        int _x;
        int _y;
        QPainter painter(this);
        painter.setPen(QColor(0,0,0));
        painter.setBrush(QColor(100,255,255));
        painter.drawRect(_x ,_y ,width(),height());
        painter.setPen(QColor(0,200,0));
        painter.setBrush(QColor(100,100,255));
        painter.drawText(_x ,_y, width(),height(), Qt::AlignCenter,"_text");

    }
    explicit MyButton(QString text, QWidget *parent = 0);

signals:
    void clicked(bool);
public slots:
};

#endif // MYBUTTON_H
