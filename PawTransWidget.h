#ifndef PAWTRANS_H
#define PAWTRANS_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QMouseEvent>

const unsigned char LADIA = 1;
const unsigned char KON = 2;
const unsigned char SLON = 3;
const unsigned char FERZ = 4;
const unsigned char KOROL = 5;
const unsigned char PESHKA = 6;

class PawTrans : public QWidget
{
    Q_OBJECT
private:
    unsigned char _pos;
public:
    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent *);

    explicit PawTrans(QWidget *parent = 0);

signals:
    void figureChosed(unsigned char);
public slots:
    void activ() {
        this->show();
    }
};

#endif // PAWTRANS_H
