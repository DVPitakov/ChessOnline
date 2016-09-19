#ifndef MYCONNECTIONFORM_H
#define MYCONNECTIONFORM_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QColor>
class MyConnectionForm : public QWidget
{
    Q_OBJECT
public:
    explicit MyConnectionForm(QWidget *parent = 0);
    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        QColor color1(255,255,255,200);
        QColor color2(0,0,0,200);
        painter.setBrush(color1);
        painter.setPen(color1);
        painter.drawRect(0,0,width() - 1,height() - 1);
        painter.setPen(color2);
        painter.setBrush(QColor(255,255,255));
        painter.drawText(0, 0, width(), height(), Qt::AlignCenter, "Поиск соперника");
    }

signals:
public slots:
    void friendSearch() {
        qDebug() << "friendSearch";
        this->show();
    }

    void friendFounded() {
        this->hide();
    }
};

#endif // MYCONNECTIONFORM_H
