#ifndef MAINWINDOW_H
#define MAINWINDOW_H
const int BOARD_X = 8;
const int BOARD_Y = 8;
static int counter = 0;
#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QEvent>
#include <Board.h>
#include <QPaintEvent>
#include <QPushButton>
#include <QLabel>
#include <mylabel.h>
#include <MyMenue.h>
#include "NetManager.h"
#include "MyUser.h"
#include "MyConnectionWindow.h"
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MyConnectionForm * connectionForm;
    MyUser *whiteUser;
    MyUser *blackUser;
    NetManager *ws;
    Bord *bord;
    QPushButton* pushButton;
    QPushButton* menueButton;
    MyMenue* menue;
    MainWindow(QWidget *parent = 0);
    bool listen_now;
    QTime timer;
    ~MainWindow();

    void paintEvent(QPaintEvent* event) {
        int x0 = 0;
        int y0 = 0;
        bool b =  width() > height();
        int awidth = width();
        int aheight = height();
        if (b) {
            if (double(awidth) / aheight < 1.2) {
               aheight =  awidth / 1.2;
               y0 = (height() - aheight)/2;
            }
            else if (double(awidth) / aheight > 1.3) {
                awidth = aheight * 1.3;
                x0 = (width() - awidth)/2;
            }
        }
        else {
            if (double(aheight) / awidth < 1.2) {
                awidth = aheight / 1.2;
                x0 = (width() - awidth)/2;
            } else if (double(aheight) / awidth > 1.3) {
                aheight = awidth * 1.3;
                y0 = (height() - aheight)/2;
            }
        }
        int bw;
        b = awidth > aheight;
        bw = b ? aheight : awidth;
        int w0 = 0;
        int h0 = 0;
        int dw = 0;
        int dh = 0;

        int w;
        int h;

        if (b) {
            w = awidth - aheight;
            h = aheight / 3;
        }
        else {
            w = awidth / 3;
            h = aheight - awidth;
        }
        b ? w0 = bw : h0 = bw;
        b ? dh = aheight / 3 : dw = awidth / 3;
        whiteUser->setGeometry(x0 + w0,y0 + h0, w, h);
        menueButton->setGeometry(x0 + w0 + dw, y0 + h0 +  dh, w, h);
        blackUser->setGeometry(x0 + w0 + 2 * dw, y0 + h0 + 2 * dh, w, h);
        bord->setGeometry(x0,y0,bw,bw);
        connectionForm->setGeometry(0, 0, width() ,height());
        menue->setGeometry(0,0,width(),height());

    }


signals:
    void readyToShow(char);

public slots:
    void chooseEndMenue(char couse) {
        if(couse == 0) {
            menue->showFailMenue();
        }
        else if (couse == 25) {
            menue->showWinMenue();
        }
        else if (couse == 45) {
            menue->showFailMenue();
        }
        else if (couse == 100) {
            menue->showWinMenue();
        }
    }

    void buttonManager(QString eventName) {
        if (eventName ==  "sdatsa") {
            menue->showFailMenue();
            ws->sendGameEnd(100,0);
        }
        else if (eventName ==  "online") {
            connectionForm->friendSearch();
            ws->run();
        }
        else if (eventName ==  "continue") {
            bord->restart();
            menue->showStartGame();
            whiteUser->setIsUser(false);
            blackUser->setIsUser(false);
            menue->update();
        }
        else if (eventName == "return") {
            menue->hide();
            bord->setHidden(false);
        }
        else if (eventName ==  "settings") {

        }
        else if (eventName ==  "exit") {
            this->close();
        }
        else if (eventName == "nichia") {
            ws->sendNichia();
            menue->showWait();
        }
        else if (eventName == "breakGame") {

        }
        else if (eventName == "sayYes") {
            ws->sayYes();
            menue->showNichia();
        }
        else if (eventName == "sayNot") {
            ws->sayNot();
            menue->setHidden(true);
        }
        else {
        }
    }

    void activeBoard() {
        bord->setEnabled(true);
        menueButton->setEnabled(true);
    }

    void startGame(int color) {
        activeBoard();
        whiteUser->setMyStep(true);
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
        menue->setEnabled(true);
        menue->setHidden(false);
        emit readyToShow(1);
    }
};

#endif // MAINWINDOW_H
