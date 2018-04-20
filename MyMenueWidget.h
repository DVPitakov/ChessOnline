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
    void startMenue();
    void gameMenue();
    void failMenue();
    void disconnectMenue();
    void winMenue();
    void nichiaMenue();
    void staticNichia();
    void waitMenue();

    void addButton(QString eventName, QString buttonName, QString buttonType = "button");

    void releaseButton();

    explicit MyMenue(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent* event);

signals:
    void buttonClicked(QString);

public slots:
    void showStartGame();
    void showGameMenue();
    void showWinMenue();
    void showWait();
    void showFailMenue();
    void showDisconnectMenue();
    void proposedNichia();
    void showNichia();

};
#endif // MYMENUE_H
