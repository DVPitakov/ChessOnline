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

    void releaseButton();

    explicit MyMenue(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent* event);

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
