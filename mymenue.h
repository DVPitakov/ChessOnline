#ifndef MYMENUE_H
#define MYMENUE_H

#include <QWidget>
#include <QPainter>
#include <mylabel.h>
#include <QPaintEvent>
#include <QDebug>
#include <QMouseEvent>

struct ButtonInfo {
    QString buttonActionName;
    QString buttonText;
    char type {0};
};

class MyMenue : public QWidget
{
    Q_OBJECT
    ButtonInfo buttonList[10];
    int buttonListLen{0};
public:
    void startMenue() {
        addButton("online", "Онлайн");
        addButton("oneUser", "Один игрок");
        addButton("twoUsers", "Два игрока");
    }
    void gameMenue() {

    }
    void failMenue() {
        addButton("defeat", "Вы проиграли");
        addButton("continue", "Ок");
    }
    void winMenue() {
        addButton("victory", "Вы выиграли");
        addButton("continue", "Ок");
    }
    void pawTrensformationMenue() {

    }

    void addButton(QString eventName, QString buttonName) {
        buttonList[buttonListLen].buttonActionName = eventName;
        buttonList[buttonListLen].buttonText = buttonName;
        buttonListLen += 1;
    }

    void releaseButton() {
        buttonListLen = 0;
    }

    explicit MyMenue(QWidget *parent = 0);
    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        QColor color1(255,255,255,200);
        QColor color2(0,0,0,200);
        painter.setBrush(color1);
        painter.setPen(color1);
        painter.drawRect(0,0,width() - 1,height() - 1);
        painter.setPen(color2);
        painter.setBrush(QColor(255,255,255));

        for(int i = 0; i < buttonListLen; i++) {
            painter.drawRect(width() * 0.05 ,height() * (0.1 + i * 0.22) ,width() * 0.9 ,height() * 0.2);
            painter.drawText(width() * 0.05 ,height() * (0.1 + i * 0.22) ,width() * 0.9 ,height() * 0.2, Qt::AlignCenter,buttonList[i].buttonText);
        }
    }
    void mouseReleaseEvent(QMouseEvent* event) {
        int x = event->x();
        int y = event->y();
        for (int i = 0; i < buttonListLen; i++) {
            if (width() * 0.05 < x && height() * (0.1 + 0.22 * i) < y && width() * 0.95 > x && height() * (0.3 + 0.22 * i) > y) {
                qDebug() << "event is: " << buttonList[i].buttonActionName;
                emit buttonClicked(buttonList[i].buttonActionName);
            }
        }
    }

signals:
    void buttonClicked(QString);

public slots:
    void showStartGame() {
        releaseButton();
        startMenue();
        this->show();
    }
    void showWinMenue() {
        releaseButton();
        winMenue();
        this->show();
    }
    void showFailMenue() {
        releaseButton();
        failMenue();
        this->show();
    }
};

#endif // MYMENUE_H
