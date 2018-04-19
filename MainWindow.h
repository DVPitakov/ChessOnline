#ifndef MAINWINDOW_H
#define MAINWINDOW_H
const int BOARD_X = 8;
const int BOARD_Y = 8;
static int counter = 0;
#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QEvent>
#include <BoardWidget.h>
#include <QPaintEvent>
#include <QPushButton>
#include <QLabel>
#include <MyMenueWidget.h>
#include "NetManager.h"
#include "MyUserWidget.h"
#include "MyConnectionStatusWidget.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent* event);

private:
    MyConnectionStatusWidget* connectionForm;
    MyUser* whiteUser;
    MyUser* blackUser;
    NetManager* netManager;
    BordWidget* bord;
    QPushButton* pushButton;
    QPushButton* menueButton;
    MyMenue* menue;
    bool listenNow;
    QTimer timer;

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
            netManager->sendGameEnd(100,0);
        }
        else if (eventName ==  "online") {
            connectionForm->friendSearch();
            netManager->run();
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
            netManager->sendNichia();
            menue->showWait();
        }
        else if (eventName == "breakGame") {

        }
        else if (eventName == "sayYes") {
            netManager->sayYes();
            menue->showNichia();
        }
        else if (eventName == "sayNot") {
            netManager->sayNot();
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
