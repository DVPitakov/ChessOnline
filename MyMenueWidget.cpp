#include "MyMenueWidget.h"

MyMenue::MyMenue(QWidget *parent) : QWidget(parent) {
     backGround = QImage(":/background.jpg");
}

void MyMenue::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QColor color1(255,255,255);
    QColor color2(0,0,0);
    painter.setBrush(color1);
    painter.setPen(color1);
    painter.drawRect(0,0,width() - 1,height() - 1);
    painter.setPen(color2);
    painter.setBrush(QColor(255,255,255));
    QImage backGround2 = backGround.scaled(width(),height());
     painter.drawImage(0,0, backGround2);

    for(int i = 0; i < buttonListLen; i++) {

        if (buttonList[i].type == "button") {
            painter.drawRect(width() * 0.05 ,height() * (0.1 + i * 0.22) ,width() * 0.9 ,height() * 0.2);
            painter.drawText(width() * 0.05 ,height() * (0.1 + i * 0.22) ,width() * 0.9 ,height() * 0.2, Qt::AlignCenter,buttonList[i].buttonText);
        }
        else if (buttonList[i].type == "header"){
            painter.drawText(width() * 0.05 ,height() * (0.1 + i * 0.22) ,width() * 0.9 ,height() * 0.2, Qt::AlignCenter,buttonList[i].buttonText);
        }
    }
}

void MyMenue::addButton(QString eventName, QString buttonName, QString buttonType) {
    buttonList[buttonListLen].buttonActionName = eventName;
    buttonList[buttonListLen].type = buttonType;
    buttonList[buttonListLen].buttonText = buttonName;
    buttonListLen += 1;
}


void MyMenue::releaseButton() {
    buttonListLen = 0;
}

void MyMenue::mouseReleaseEvent(QMouseEvent* event) {
    int x = event->x();
    int y = event->y();
    for (int i = 0; i < buttonListLen; i++) {
        if (width() * 0.05 < x && height() * (0.1 + 0.22 * i) < y && width() * 0.95 > x && height() * (0.3 + 0.22 * i) > y) {
            emit buttonClicked(buttonList[i].buttonActionName);
        }
    }
}
