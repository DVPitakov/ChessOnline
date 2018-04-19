#include "PawTransWidget.h"

PawTrans::PawTrans(QWidget *parent) : QWidget(parent) {
    setGeometry(parent->width() * 0.1, parent->height() * 0.1, parent->width() * 0.8, parent->height() * 0.8);
}
