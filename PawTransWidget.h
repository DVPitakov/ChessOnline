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
    void mouseReleaseEvent(QMouseEvent* event);

    void paintEvent(QPaintEvent *);

    explicit PawTrans(QWidget *parent = 0);

signals:
    void figureChosed(char);
public slots:
    void activ() {
        this->show();
    }
};

#endif // PAWTRANS_H
