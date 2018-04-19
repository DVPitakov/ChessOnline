#ifndef PAWTRANS_H
#define PAWTRANS_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>

const char LADIA = 1;
const char KON = 2;
const char SLON = 3;
const char FERZ = 4;
const char KOROL = 5;
const char PESHKA = 6;

class PawTrans : public QWidget
{
    Q_OBJECT
private:
    char _pos;
public:
    void mouseReleaseEvent(QMouseEvent* event) {
        int x = event->x();
        int y = event->y();
        if (width() * 0.05 < x && height() * 0.10 < y && width() * 0.95 > x && height() * 0.30 > y) {
            emit figureChosed(FERZ);
            this->hide();
            return;
        }
        if (width() * 0.05 < x && height() * 0.31 < y && width() * 0.95 > x && height() * 0.51 > y) {
            emit figureChosed(KON);
            this->hide();
            return;
        }
        if (width() * 0.05 < x && height() * 0.52 < y && width() * 0.95 > x && height() * 0.72 > y) {
            emit figureChosed(SLON);
            this->hide();
            return;
        }
        if (width() * 0.05 < x && height() * 0.73 < y && width() * 0.95 > x && height() * 0.93 > y) {
            emit figureChosed(LADIA);
            this->hide();
            return;
        }
    }

    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        QColor color1(255,255,255,200);
        QColor color2(0,0,0,200);
        painter.setBrush(color1);
        painter.setPen(color1);
        painter.drawRect(0,0,width(),height());
        painter.setPen(color2);
        painter.setBrush(QColor(255,255,255));
        painter.drawRect(width() * 0.05 ,height() * 0.1 ,width() * 0.9 ,height() * 0.2);
        painter.drawText(width() * 0.05 ,height() * 0.1 ,width() * 0.9 ,height() * 0.2, Qt::AlignCenter,"Ферзь");
        painter.drawRect(width() * 0.05 ,height() * 0.31 ,width() * 0.9 ,height() * 0.2);
        painter.drawText(width() * 0.05 ,height() * 0.31 ,width() * 0.9 ,height() * 0.2, Qt::AlignCenter,"Конь");
        painter.drawRect(width() * 0.05 ,height() * 0.52 ,width() * 0.9 ,height() * 0.2);
        painter.drawText(width() * 0.05 ,height() * 0.52 ,width() * 0.9 ,height() * 0.2, Qt::AlignCenter,"Слон");
        painter.drawRect(width() * 0.05 ,height() * 0.73 ,width() * 0.9 ,height() * 0.2);
        painter.drawText(width() * 0.05 ,height() * 0.73 ,width() * 0.9 ,height() * 0.2, Qt::AlignCenter,"Ладья");

    }

    explicit PawTrans(QWidget *parent = 0);

signals:
    void figureChosed(char);
public slots:
    void activ() {
        this->show();
    }
};

#endif // PAWTRANS_H
