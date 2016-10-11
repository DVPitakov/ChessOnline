#include "MyTimer.h"

MyTimer::MyTimer(QWidget *parent) : QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
}

