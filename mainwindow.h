#ifndef MAINWINDOW_H
#define MAINWINDOW_H
const int BOARD_X = 8;
const int BOARD_Y = 8;
static int counter = 0;
#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QEvent>
#include <QDebug>
#include <board.h>
#include <QPaintEvent>
#include <QPushButton>
#include <QLabel>
#include <mylabel.h>
#include <mymenue.h>
#include "WebSocketsConnector.h"
#include "MyUser.h"
#include "MyConnectionWindow.h"
#include "MyTimer.h"
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MyConnectionForm * connectionForm;
    MyUser *whiteUser;
    MyUser *blackUser;
    MyTimer* myTimer;
    EchoClient *ws;
    Bord *bord;
    QPushButton* pushButton;
    QPushButton* menueButton;
    MyMenue* menue;
    bool online{0};

    MainWindow(QWidget *parent = 0);
    bool listen_now;
    QTime timer;
    ~MainWindow();
    void paintEvent(QPaintEvent* event) {
        int bw;
        (width() > height() * 0.9) ? bw = height() * 0.9: bw = width();
        whiteUser->setGeometry(bw * 1.02 ,0, 0.2 * bw, 0.2 * bw);
        blackUser->setGeometry(bw * 1.02, 0.22 * bw, 0.2 * bw, 0.2 * bw);
        myTimer->setGeometry(bw * 1.02, 0.42 * bw, 0.2 * bw, 0.2 * bw);
        bord->setGeometry(0,0,bw,bw);
        connectionForm->setGeometry(width() * 0.05 ,height() * 0.05, width()*0.9, height() * 0.9);
        menueButton->setGeometry(width() * 0.62, height() * 0.91, width()*0.3, height() * 0.09);
        menue->setGeometry(width() * 0.05 ,height() * 0.05, width()*0.9, height() * 0.9);

    }


signals:
    readyToShow(char);
public slots:
    void buttonManager(QString eventName) {
        if (eventName ==  "online") {
            connectionForm->friendSearch();
            ws->open();
        }
        else if (eventName ==  "onePlayer") {}
        else if (eventName ==  "twoPlayers") {}
        else if (eventName ==  "exit") {}
        else if (eventName == "breakGame") {}
        else {}
    }

    void onlineGameChosed() {
        online == true;
    }

    void activeBoard() {
        bord->setEnabled(true);
        menueButton->setEnabled(true);
    }
    void startGame(int color) {
        activeBoard();
        whiteUser->setMyStep(true);
        qDebug() << "color worked";
        if(color) {
            whiteUser->setIsUser(true);
            bord->setColor(0);
        }
        else {
            blackUser->setIsUser(true);
            bord->setColor(1);
        }
        update();
    }

    void showMenue() {
        bord->setEnabled(false);
        menueButton->setEnabled(false);
        emit readyToShow(1);
    }
};

#endif // MAINWINDOW_H
