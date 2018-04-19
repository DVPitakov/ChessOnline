#ifndef MYMENUE_H
#define MYMENUE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QImage>

class MyMenue : public QWidget
{
    Q_OBJECT
    struct ButtonInfo {
        QString buttonActionName;
        QString buttonText;
        QString type{"button"};
    };

    ButtonInfo buttonList[10];
    int buttonListLen{0};
    QImage backGround;
public:
    void startMenue() {
        addButton("online", "Играть онлайн");
        addButton("exit", "Выход");
    }
    void gameMenue() {
        addButton("return", "Вернуться");
        addButton("sdatsa", "Сдаться");
        addButton("nichia", "Предложить ничью");
        addButton("exit", "Выход");
    }
    void failMenue() {
        addButton("defeat", "Вы проиграли", "header");
        addButton("continue", "Ок");
    }
    void disconnectMenue() {
        addButton("defeat", "Соединение разорвано", "header");
        addButton("continue", "Ок");
    }
    void winMenue() {
        addButton("victory", "Вы выиграли", "header");
        addButton("continue", "Ок");
    }
    void nichiaMenue() {
        addButton("defeat", "Противник предлагает ничью", "header");
        addButton("sayYes", "Согласиться");
        addButton("sayNot", "Отказаться");
    }
    void staticNichia() {
        addButton("continue", "Ничья", "header");
        addButton("continue", "Ок");
    }
    void waitMenue() {
        addButton("info", "Ожидание ответа", "header");
    }

    void pawTrensMenue() {

    }

    void addButton(QString eventName, QString buttonName, QString buttonType = "button") {
        buttonList[buttonListLen].buttonActionName = eventName;
        buttonList[buttonListLen].type = buttonType;
        buttonList[buttonListLen].buttonText = buttonName;
        buttonListLen += 1;
    }

    void releaseButton() {
        buttonListLen = 0;
    }

    explicit MyMenue(QWidget *parent = 0);
    void paintEvent(QPaintEvent *) {
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
    void mouseReleaseEvent(QMouseEvent* event) {
        int x = event->x();
        int y = event->y();
        for (int i = 0; i < buttonListLen; i++) {
            if (width() * 0.05 < x && height() * (0.1 + 0.22 * i) < y && width() * 0.95 > x && height() * (0.3 + 0.22 * i) > y) {
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
        update();
    }

    void showGameMenue() {
        releaseButton();
        gameMenue();
        this->show();
        update();
    }

    void showWinMenue() {
        releaseButton();
        winMenue();
        this->show();
        update();
    }

    void showWait() {
        releaseButton();
        waitMenue();
        this->show();
        update();
    }

    void showFailMenue() {
        releaseButton();
        failMenue();
        this->show();
        update();
    }

    void showDisconnectMenue() {
        releaseButton();
        disconnectMenue();
        this->show();
        update();
    }

    void proposedNichia() {
        releaseButton();
        nichiaMenue();
        this->show();
        update();
    }

    void showNichia() {
        releaseButton();
        staticNichia();
        this->show();
        update();
    }

};

#endif // MYMENUE_H
