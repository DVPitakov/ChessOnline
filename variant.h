#ifndef VARIANT_H
#define VARIANT_H

#include <QWidget>
#include <QPainter>
#include <QVBoxLayout>
#include <QPushButton>
class Variant : public QWidget
{
    Q_OBJECT
public:
    char mas[64];
    QString text;
    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        painter.setBrush(Qt::black);
        painter.setPen(Qt::black);
        painter.drawRect(0,0,this->width(),this->height());
    }
    Variant(QWidget *parent = 0);
    void setBord(char* source) {
        memcpy(mas, source, 64);
    }


signals:

public slots:
};

#endif // VARIANT_H
