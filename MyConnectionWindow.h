#ifndef MYCONNECTIONFORM_H
#define MYCONNECTIONFORM_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>
class MyConnectionForm : public QWidget
{
    bool isConnected{false};
    Q_OBJECT
public:
    explicit MyConnectionForm(QWidget *parent = 0);
    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        QColor color1(255,255,255,200);
        QColor color2(0,0,0);
        painter.setBrush(color1);
        painter.setPen(color1);
        painter.drawRect(0,0,width() - 1,height() - 1);
        painter.setPen(color2);
        painter.setBrush(QColor(255,255,255));
        painter.drawRect(width() * 0.29 , 0, width() * 0.52, height() * 0.8);
        painter.drawText(width() * 0.3 , 0, width(), height() * 0.1, Qt::AlignLeft, "Поиск сервера");
        painter.drawText(width() * 0.7, 0, width() * 0.1, height() * 0.3, Qt::AlignRight, (isConnected?"true":"false"));
        painter.drawText(width() * 0.3, height() * 0.04, width(), height() * 0.1, Qt::AlignLeft, "Поиск соперника");
        painter.drawText(width() * 0.7, height() * 0.04, width() * 0.1, height() * 0.3, Qt::AlignRight, ("false"));
    }

signals:
public slots:
    void connected() {
        isConnected = true;
        update();
    }

    void friendSearch() {
        this->show();
    }

    void friendFounded() {
        this->hide();
    }
};

#endif // MYCONNECTIONFORM_H
