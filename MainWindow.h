#ifndef MAINWINDOW_H
#define MAINWINDOW_H
const int BOARD_X = 8;
const int BOARD_Y = 8;
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
    void paintEvent(QPaintEvent*);

private:
    MyConnectionStatusWidget* connectionForm;
    MyUser* user;
    NetManager* netManager;
    BordWidget* board;
    QPushButton* menueButton;
    QLabel* currentPlayerLabel;
    MyMenue* menue;
    bool listenNow;
    QTimer timer;

signals:
    void readyToShow(unsigned char);

public slots:
    void chooseEndMenue(EndCouse couse);

    void buttonManager(QString eventName);

    void activeBoard();

    void startGame(int color);

    void showMenue();

    void showURLInputDialog();

    void changeCurUser(Storona userColor);
};

#endif // MAINWINDOW_H
