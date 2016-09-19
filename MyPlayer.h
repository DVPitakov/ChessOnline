#ifndef MYPLAYER_H
#define MYPLAYER_H

#include <QObject>

class MyPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MyPlayer(QObject *parent = 0);

signals:
    void myStep(int, int);

public slots:
};

#endif // MYPLAYER_H
