#include "PawTransWidget.h"

PawTrans::PawTrans(QWidget *parent) : QWidget(parent) {
    setGeometry(parent->width() * 0.1, parent->height() * 0.1, parent->width() * 0.8, parent->height() * 0.8);
}

void PawTrans::mouseReleaseEvent(QMouseEvent* event) {
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

void PawTrans::paintEvent(QPaintEvent *) {
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
